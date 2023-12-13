#include <limits>
#include "inc/quantitizer.h"

Quantitizer::Quantitizer(Image image, int level) {
  im_ = image;
  if(level == 0) {
    lvl_ = 0;
  } else {
    lvl_ = 1;
    for(int i = 0; i < level - 1; i++) {
      lvl_ <<= 1;
    }
  }
  if(lvl_ > 0) {
    Pixel y_start = avg_vector(image.pixels);
    Y_.push_back(y_start);
  }
  result_pixels_ =
      std::vector<std::vector<Pixel>>(
          image.height, std::vector<Pixel>(
              image.height, {0,0,0}));
}

void Quantitizer::quantify(double epsilon) {
  while(Y_.size() < lvl_) {
    std::vector<Pixel> new_y;
    for(auto p : Y_) {
      Pixel p1 = pixelPerturbation(p, 1);
      Pixel p2 = pixelPerturbation(p, -1);
      new_y.push_back(p1);
      new_y.push_back(p2);
    }
    Y_ = new_y;
    distortion_ = splitImage(epsilon);
  }
}

void Quantitizer::outputImage(std::string in_name, std::string out_name) {
  std::fstream f_in, f_out;
  f_in.open(in_name, std::ios::in);
  f_out.open(out_name, std::ios::out);

  for(int i = 0; i < 18; i++) {
    int val = f_in.get();
    f_out.put(val);
  }
  for(int i = im_.height - 1; i >= 0; i--) {
    for(int j = 0; j < im_.width; j++) {
      for(int k = 0; k < 3; k++) {
        f_in.get();
      }
      f_out.put(result_pixels_.at(i).at(j).blue);
      f_out.put(result_pixels_.at(i).at(j).green);
      f_out.put(result_pixels_.at(i).at(j).red);
    }
  }

  int tail = f_in.get();
  while(!f_in.eof()) {
    f_out.put(tail);
    tail = f_in.get();
  }

  f_in.close();
  f_out.close();
}

double Quantitizer::getResultDistortion() const {
  return distortion_;
}

double Quantitizer::signalNoiseRatio() {
  double res = 0.0;
  double size = im_.height * im_.width;
  for(int i = 0; i < im_.height; i++) {
    for(int j = 0; j < im_.width; j++) {
      size_t r = im_.pixels.at(i).at(j).red;
      size_t g = im_.pixels.at(i).at(j).green;
      size_t b = im_.pixels.at(i).at(j).blue;
      res += r * r + g * g + b * b;
      res /= (double)size;
    }
  }
  return res / distortion_;
}

Pixel Quantitizer::pixelPerturbation(Pixel p, int perturbation) {
  p.red = (p.red + perturbation + 256) % 256;
  p.green = (p.green + perturbation + 256) % 256;
  p.blue = (p.blue + perturbation + 256) % 256;
  return p;
}

double Quantitizer::splitImage(double epsilon) {
  double curr_d = 0.0;
  double prev_d = 0.0;
  double error = 1.0 + epsilon;
  while(error >= epsilon) {
    std::vector<std::vector<Pixel>> V(Y_.size(), std::vector<Pixel>());
    std::vector<std::vector<std::pair<int, int>>> pixels_coords(Y_.size(), std::vector<std::pair<int, int>>());
    for(int i = 0; i < im_.height; i++) {
      for(int j = 0; j < im_.width; j++) {
        size_t best_index = 0;
        size_t min_dist = std::numeric_limits<size_t>::max();
        for(int k = 0; k < Y_.size(); k++) {
          size_t dist = distance(im_.pixels.at(i).at(j), Y_.at(k));
          if(dist < min_dist) {
            best_index = k;
            min_dist = dist;
          }
        }
        V.at(best_index).push_back(im_.pixels.at(i).at(j));
        pixels_coords.at(best_index).push_back({i, j});
      }
    }

    for(int i = 0; i < Y_.size(); i++) {
      if(V.at(i).size() > 0) {
        Y_.at(i) = avg_vector(V.at(i));
        for(auto pair : pixels_coords.at(i)) {
          result_pixels_.at(pair.first).at(pair.second) = Y_.at(i);
        }
      }
    }

    prev_d = curr_d;
    curr_d = calculateDistortion(V);

    error = (curr_d - prev_d) / curr_d;
  }
  return curr_d;
}

Pixel Quantitizer::avg_vector(std::vector<std::vector<Pixel>> &pixels) {
  if(pixels.size() == 0)
    return {0,0,0};
  size_t size = 0;
  size_t red = 0;
  size_t green = 0;
  size_t blue = 0;
  for(int i = 0; i < pixels.size(); i++) {
    for(int j = 0; j < pixels.at(i).size(); j++) {
      red += pixels.at(i).at(j).red;
      green += pixels.at(i).at(j).green;
      blue += pixels.at(i).at(j).blue;
      size++;
    }
  }
  red /= size;
  green /= size;
  blue /= size;
  return {(int)red, (int)green, (int)blue};
}

Pixel Quantitizer::avg_vector(std::vector<Pixel> &pixels) {
  if(pixels.size() == 0)
    return {0,0,0};
  size_t red = 0;
  size_t green = 0;
  size_t blue = 0;
  for(auto pix : pixels) {
    red += pix.red;
    green += pix.green;
    blue += pix.blue;
  }
  red /= pixels.size();
  green /= pixels.size();
  blue /= pixels.size();
  return {(int)red, (int)green, (int)blue};
}

size_t Quantitizer::distance(Pixel a, Pixel b) {
  size_t dist = 0;
  dist += std::abs(a.red - b.red);
  dist += std::abs(a.green - b.green);
  dist += std::abs(a.blue - b.blue);
  return dist;
}

double Quantitizer::calculateDistortion(std::vector<std::vector<Pixel>> V) {
  double sum = 0.0;
  for(int i = 0; i < V.size(); i++) {
    for(auto pix : V.at(i)) {
      size_t dist = distance(pix, Y_.at(i));
      sum += (double)(dist * dist) / (double)(im_.width * im_.height);
    }
  }
  return sum;
}