#include <cmath>
#include <unordered_map>
#include <queue>
#include "inc/quantitizer.h"

Image Quantitizer::encode(Image im, int bits_count) {

  std::vector<Pixel> high_pass_filtered = highPassFilterImage(im);
  std::vector<std::vector<int>> quant_maps = quantify(high_pass_filtered, bits_count);
  std::vector<Pixel> quant_high = reconstructImageFromQuantizationMap(quant_maps, high_pass_filtered);

  std::vector<Pixel> low_pass_filtered = lowPassFilterImage(im);
  std::vector<Pixel> diff_encoded_low = encodeDifferentially(low_pass_filtered);
  quant_maps = quantify(diff_encoded_low, bits_count);
  std::vector<Pixel> diff_encoded_min_err_low = encodeDifferentiallyMinimizingError(low_pass_filtered, quant_maps);

  Image sum = sumImages(diff_encoded_min_err_low, quant_high, im);
  std::cout << "Statistics\n";
  signalNoiseRatio(im, sum);
  return sum;
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

std::vector<Pixel> Quantitizer::encodeDifferentiallyMinimizingError(std::vector<Pixel> pixels,
                                                                    std::vector<std::vector<int>> quant_ranges) {
  std::vector<Pixel> new_pixels;
  Pixel reconstruction = {0, 0, 0};
  for(int i = 0; i < pixels.size(); i++) {
    Pixel new_pix;
    if(i == 0) {
      int range_index = findIndex(pixels.at(i).red, quant_ranges.at(0));
      new_pix.red = quant_ranges.at(0).at(range_index);
      range_index = findIndex(pixels.at(i).green, quant_ranges.at(1));
      new_pix.green = quant_ranges.at(1).at(range_index);
      range_index = findIndex(pixels.at(i).blue, quant_ranges.at(2));
      new_pix.blue = quant_ranges.at(2).at(range_index);
    } else {
      new_pix = pixels.at(i) - reconstruction;
      int range_index = findIndex(new_pix.red, quant_ranges.at(0));
      new_pix.red = quant_ranges.at(0).at(range_index);
      range_index = findIndex(new_pix.green, quant_ranges.at(1));
      new_pix.green = quant_ranges.at(1).at(range_index);
      range_index = findIndex(new_pix.blue, quant_ranges.at(2));
      new_pix.blue = quant_ranges.at(2).at(range_index);
    }
    new_pixels.push_back(new_pix);
    reconstruction = reconstruction + new_pix;
  }
  return new_pixels;
}

std::vector<std::vector<int>> Quantitizer::quantify(std::vector<Pixel> input, int k) {
  int lvl = 1 << (k - 1);
  std::vector<int> red_pixels;
  std::vector<int> green_pixels;
  std::vector<int> blue_pixels;
  for(auto pix : input) {
    red_pixels.push_back(pix.red);
    green_pixels.push_back(pix.green);
    blue_pixels.push_back(pix.blue);
  }
  std::vector<std::vector<int>> quantizers;
  quantizers.push_back(quantifySingleChannel(red_pixels, lvl));
  quantizers.push_back(quantifySingleChannel(green_pixels, lvl));
  quantizers.push_back(quantifySingleChannel(blue_pixels, lvl));
  return quantizers;
}

std::vector<int> Quantitizer::quantifySingleChannel(std::vector<int> single_channel, int lvl) {
  int min = std::numeric_limits<int>::max();
  int max = std::numeric_limits<int>::min();
  for(auto val : single_channel) {
    if(val < min)
      min = val;
    else if(val > max)
      max = val;
  }
  int dist = max - min;
  int step = dist / lvl;
  std::vector<int> ranges;
  while(ranges.size() < lvl) {
    ranges.push_back(min);
    min += step;
  }
  return ranges;
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

int Quantitizer::findIndex(int val, std::vector<int> range) {
  int ranges_index = 0;
  while(ranges_index < range.size() - 1) {
    if(val > range.at(ranges_index + 1))
      ranges_index++;
    else
      break;
  }
  return ranges_index;
}

std::vector<Pixel> Quantitizer::reconstructImageFromQuantizationMap(
    std::vector<std::vector<int>> ranges, std::vector<Pixel> input) {
  for(auto & pix : input) {
    int range_index = findIndex(pix.red, ranges.at(0));
    pix.red = ranges.at(0).at(range_index);
    range_index = findIndex(pix.green, ranges.at(1));
    pix.green = ranges.at(1).at(range_index);
    range_index = findIndex(pix.blue, ranges.at(2));
    pix.blue = ranges.at(2).at(range_index);
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
  }

  int h_ind = -1;
  for(int i = 0; i < y.size() * 2; i++) {
    if(i % original_im.width == 0)
      h_ind++;

    if(i%2 == 0) {
      original_im.pixels.at(h_ind).at(i % original_im.width) = y_decoded.at(i / 2) + z.at(i / 2);
    } else {
      original_im.pixels.at(h_ind).at(i % original_im.width) = y_decoded.at(i / 2) - z.at(i / 2);
    }
  }
  return original_im;
}