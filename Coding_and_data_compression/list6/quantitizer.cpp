#include <cmath>
#include <unordered_map>
#include <queue>
#include "inc/quantitizer.h"

Image Quantitizer::encode(Image im, int bits_count) {
  std::vector<Pixel> original_im_pixels = putToSingleVector(im.pixels);
  std::vector<Pixel> high_pass_filtered = highPassFilterImage(im);
  std::vector<std::pair<int, Pixel>> quant_high_map = quantifyNonuniform(high_pass_filtered, bits_count);
  std::vector<Pixel> quant_high = reconstructImageFromQuantizationMap(quant_high_map, high_pass_filtered);

  std::vector<Pixel> low_pass_filtered = lowPassFilterImage(im);
  std::vector<Pixel> diff_encoded_low = encodeDifferentially(low_pass_filtered);
  std::vector<std::pair<int, Pixel>> quant_diff_map = quantifyNonuniform(diff_encoded_low, bits_count);
  std::vector<Pixel> quant_diff = reconstructImageFromQuantizationMap(quant_diff_map, diff_encoded_low);
  std::vector<Pixel> min_error_diff_encoded_low = encodeDifferentiallyMinimizingError(low_pass_filtered, quant_diff_map);
  quant_diff_map = quantifyNonuniform(min_error_diff_encoded_low, bits_count);
  quant_diff = reconstructImageFromQuantizationMap(quant_diff_map, min_error_diff_encoded_low);

//  errors.clear();
//  for(int i = 0; i < quant_diff.size(); i++) {
//    errors.push_back(diff_encoded_low.at(i) - minimized_error_quant_diff.at(i));
//    std::cout << errors.at(i).red << " " << errors.at(i).green << " " << errors.at(i).blue << std::endl;
//  }

//  for(auto pix : quant_high) {
//    std::cout << pix.red << " " << pix.green << " " << pix.blue << std::endl;
//  }
  Image sum = sumImages(quant_diff, quant_high, im);
  std::cout << "Statistics\n";
  signalNoiseRatio(im, sum);
  return sum;
}

std::vector<Pixel> Quantitizer::putToSingleVector(std::vector<std::vector<Pixel>> pixels) {
  std::vector<Pixel> result;
  for(auto row : pixels) {
    for(auto pix : row) {
      result.push_back(pix);
    }
  }
  return result;
}

std::vector<Pixel> Quantitizer::lowPassFilterImage(Image im) {
  std::vector<Pixel> pixels;
  for(int i = 0; i < im.height; i++) {
    for(int j = 0; j < im.width; j++) {
      if((i + j) % 2 == 0)
        continue;
      if(i == im.height - 1 && j == im.width - 1)
        break;
      else if(j == 0) {
        pixels.push_back((im.pixels.at(i).at(j) + im.pixels.at(i - 1).at(im.width - 1)) / 2);
      } else {
        pixels.push_back((im.pixels.at(i).at(j) + im.pixels.at(i).at(j - 1)) / 2);
      }
    }
  }
  return pixels;
}

std::vector<Pixel> Quantitizer::highPassFilterImage(Image im) {
  std::vector<Pixel> pixels;
  for(int i = 0; i < im.height; i++) {
    for(int j = 0; j < im.width; j++) {
      if((i + j) % 2 == 0)
        continue;
      if(i == im.height - 1 && j == im.width - 1)
        break;
      else if(j == 0) {
        pixels.push_back((im.pixels.at(i).at(j) - im.pixels.at(i - 1).at(im.width - 1)) / 2);
      } else {
        pixels.push_back((im.pixels.at(i).at(j) - im.pixels.at(i).at(j - 1)) / 2);
      }
    }
  }
  return pixels;
}

std::vector<Pixel> Quantitizer::encodeDifferentially(std::vector<Pixel> pixels) {
  std::vector<Pixel> new_pixels;
  new_pixels.push_back(pixels.at(0));
  for(int i = 1; i < pixels.size(); i++) {
    new_pixels.push_back(pixels.at(i) - pixels.at(i-1));
  }
  return new_pixels;
}

std::vector<Pixel> Quantitizer::encodeDifferentiallyMinimizingError(
    std::vector<Pixel> pixels,
    std::vector<std::pair<int, Pixel>> quantization_map) {
  std::vector<Pixel> result;
  result.push_back(pixels.at(0));
  for(int i = 1; i < pixels.size(); i++) {
    Pixel prev_val_after_quantization;
    int best_index = 0;
    int min_dist = std::numeric_limits<int>::max();
    for(int k = 0; k < quantization_map.size(); k++) {
      int dist = distance(result.at(i-1), quantization_map.at(k).second);
      if(dist < min_dist) {
        best_index = k;
        min_dist = dist;
      }
    }
    prev_val_after_quantization = quantization_map.at(best_index).second;
    Pixel error = result.at(i-1) - prev_val_after_quantization;
//    std::cout << error.red << " " << error.green << " " << error.blue << "\n";
    result.push_back(pixels.at(i) - pixels.at(i-1));
    result.at(i) + error;
  }
  return result;
}

std::vector<std::pair<int, Pixel>> Quantitizer::quantifyNonuniform(std::vector<Pixel> input, int k) {
  int lvl = 1 << (k-1);
  double epsilon = 0.01;
  std::vector<Pixel> Y;
  Y.push_back(avg_vector(input));
  std::vector<std::pair<int, Pixel>> pixels_map;

  while(Y.size() < lvl) {
    std::vector<Pixel> new_y;
    for(auto p : Y) {
      Pixel p1 = pixelPerturbation(p, 5);
      Pixel p2 = pixelPerturbation(p, -5);
      new_y.push_back(p1);
      new_y.push_back(p2);
    }
    Y = new_y;
    pixels_map = splitImage(epsilon, lvl, input, Y);
  }
  return pixels_map;
}

Pixel Quantitizer::pixelPerturbation(Pixel p, int perturbation) {
  p.red = (p.red + perturbation + 256) % 256;
  p.green = (p.green + perturbation + 256) % 256;
  p.blue = (p.blue + perturbation + 256) % 256;
  return p;
}

std::vector<std::pair<int, Pixel>> Quantitizer::splitImage(double epsilon, int lvl, std::vector<Pixel> input, std::vector<Pixel> Y) {
  double curr_d = 0.0;
  double prev_d = 0.0;
  double error = 1.0 + epsilon;
  std::vector<Pixel> result(input.size(), {0,0,0});
  std::vector<std::pair<int, Pixel>> pixels_map;
  while(error >= epsilon) {
    pixels_map.clear();
    std::vector<std::vector<Pixel>> V(Y.size(), std::vector<Pixel>());
    std::vector<std::vector<int>> pixels_coords(Y.size(), std::vector<int>());
    for(int i = 0; i < input.size(); i++) {
        int best_index = 0;
        int min_dist = std::numeric_limits<int>::max();
        for(int k = 0; k < Y.size(); k++) {
          int dist = distance(input.at(i), Y.at(k));
          if(dist < min_dist) {
            best_index = k;
            min_dist = dist;
          }
        }
        V.at(best_index).push_back(input.at(i));
        pixels_coords.at(best_index).push_back(i);
    }

    for(int i = 0; i < Y.size(); i++) {
      if(V.at(i).size() > 0) {
        Y.at(i) = avg_vector(V.at(i));
        for(auto index : pixels_coords.at(i)) {
          result.at(index) = Y.at(i);
          pixels_map.push_back({index, Y.at(i)});
        }
      }
    }

    prev_d = curr_d;
    curr_d = calculateDistortion(V, Y, input.size());

    error = (curr_d - prev_d) / curr_d;
  }
  return pixels_map;
}

Pixel Quantitizer::avg_vector(std::vector<Pixel> pixels) {
  if(pixels.size() == 0)
    return {0,0,0};
  long long int red = 0;
  long long int green = 0;
  long long int blue = 0;
  for(auto pix : pixels) {
    red += pix.red;
    green += pix.green;
    blue += pix.blue;
  }
  red /= (long long int)pixels.size();
  green /= (long long int)pixels.size();
  blue /= (long long int)pixels.size();
  return {(int)red, (int)green, (int)blue};
}

double Quantitizer::minSquareError(Image im1, Image im2) {
  double sum = 0.0;
  for(int i = 0; i < im1.pixels.size(); i++) {
    for(int j = 0; j < im1.pixels.at(i).size(); j++) {
      size_t dist = distance(im1.pixels.at(i).at(j), im2.pixels.at(i).at(j));
      sum += (double)(dist * dist) / (double)(im1.width * im1.height);
    }
  }
  return sum;
}

int Quantitizer::distance(Pixel a, Pixel b) {
  int dist = 0;
  dist += std::abs(a.red - b.red);
  dist += std::abs(a.green - b.green);
  dist += std::abs(a.blue - b.blue);
  return dist;
}

double Quantitizer::calculateDistortion(std::vector<std::vector<Pixel>> V, std::vector<Pixel> Y, int size) {
  double sum = 0.0;
  for(int i = 0; i < V.size(); i++) {
    for(auto pix : V.at(i)) {
      int dist = distance(pix, Y.at(i));
      sum += (double)(dist * dist) / (double)(size * size);
    }
  }
  return sum;
}

std::vector<Pixel> Quantitizer::reconstructImageFromQuantizationMap(
    std::vector<std::pair<int, Pixel>> map, std::vector<Pixel> input) {
  for(auto pair : map) {
    input.at(pair.first) = pair.second;
  }
  return input;
}

void Quantitizer::signalNoiseRatio(Image im1, Image im2) {
  double mse = minSquareError(im1, im2);
  double res = 0.0;
  double size = im1.height * im1.width;
  for (int i = 0; i < im1.height; i++) {
    for (int j = 0; j < im1.width; j++) {
      size_t r = im1.pixels.at(i).at(j).red;
      size_t g = im1.pixels.at(i).at(j).green;
      size_t b = im1.pixels.at(i).at(j).blue;
      res += r * r + g * g + b * b;
      res /= (double) size;
    }
  }
  std::cout << "Signal to noise ratio: " << res / mse << std::endl;
  std::cout << "Mean square error: " << mse << std::endl;
  minSquareChannelsError(im1, im2);
}

void Quantitizer::minSquareChannelsError(Image im1, Image im2) {
  double sum_r = 0.0;
  double sum_g = 0.0;
  double sum_b = 0.0;
  for(int i = 0; i < im1.pixels.size(); i++) {
    for(int j = 0; j < im1.pixels.at(i).size(); j++) {
      size_t dist_r = std::abs(im1.pixels.at(i).at(j).red - im2.pixels.at(i).at(j).red);
      size_t dist_g = std::abs(im1.pixels.at(i).at(j).green - im2.pixels.at(i).at(j).green);
      size_t dist_b = std::abs(im1.pixels.at(i).at(j).blue - im2.pixels.at(i).at(j).blue);
      sum_r += (double)(dist_r * dist_r) / (double)(im1.width * im1.height);
      sum_g += (double)(dist_g * dist_g) / (double)(im1.width * im1.height);
      sum_b += (double)(dist_b * dist_b) / (double)(im1.width * im1.height);
    }
  }
  std::cout << "Mean square error - red channel: " << sum_r << std::endl;
  std::cout << "Mean square error - green channel: " << sum_g << std::endl;
  std::cout << "Mean square error - blue channel: " << sum_b << std::endl;
}

Image Quantitizer::sumImages(std::vector<Pixel> y, std::vector<Pixel> z, Image original_im) {
  std::vector<Pixel> y_decoded;
  y_decoded.push_back(y.at(0));
  for(int i = 1; i < y.size(); i++) {
    y_decoded.push_back(y_decoded.at(i-1) + y.at(i));
//    std::cout << z.at(i).red << " " << z.at(i).green << " " << z.at(i).blue << " ";
  }

  int h_ind = -1;
  for(int i = 0; i < y.size() * 2; i++) {
    if(i % original_im.width == 0)
      h_ind++;

    if(i%2 == 0) {
      original_im.pixels.at(h_ind).at(i % original_im.width) = y.at(i / 2) + z.at(i / 2);
    } else {
      original_im.pixels.at(h_ind).at(i % original_im.width) = y.at(i / 2) - z.at(i / 2);
    }
//    std::cout << original_im.pixels.at(h_ind).at(i % original_im.width).red << " " << original_im.pixels.at(h_ind).at(i % original_im.width).green << " " << original_im.pixels.at(h_ind).at(i % original_im.width).blue << "\n";
  }
  return original_im;
}