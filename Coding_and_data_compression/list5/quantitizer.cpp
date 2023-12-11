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
    splitImage(epsilon);
  }
}

Pixel Quantitizer::pixelPerturbation(Pixel p, int perturbation) {
  p.red = (p.red + perturbation + 256) % 256;
  p.green = (p.green + perturbation + 256) % 256;
  p.blue = (p.blue + perturbation + 256) % 256;
  return p;
}

void Quantitizer::splitImage(double epsilon) {
  double curr_d = 0.0;
  double prev_d = 0.0;
  double error = 1.0 + epsilon;
  while(error >= epsilon) {
    std::vector<std::vector<Pixel>> V(Y_.size(), std::vector<Pixel>());
    std::vector<std::vector<std::pair<int, int>>> pixels_coords(Y_.size(), std::vector<std::pair<int, int>>());
    for(int i = 0; i < im_.width; i++) {
      for(int j = 0; j < im_.height; j++) {
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
    pixels_coords_ = pixels_coords;

    for(int i = 0; i < Y_.size(); i++) {
      if(V.at(i).size() > 0) {
        Y_.at(i) = avg_vector(V.at(i));
      }
    }

    prev_d = curr_d;
    curr_d = calculateDistortion(V);

    error = (curr_d - prev_d) / curr_d;
  }
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

size_t Quantitizer::distance(Pixel a, Pixel b) {
  size_t dist = 0;
  dist += std::abs(a.red - b.red);
  dist += std::abs(a.green - b.green);
  dist += std::abs(a.blue - b.blue);
  return dist;
}

double Quantitizer::calculateDistortion(std::vector<std::vector<Pixel>> V) {
  double sum = 0.0;

}