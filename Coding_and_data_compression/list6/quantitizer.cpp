#include <cmath>
#include <unordered_map>
#include <queue>
#include "inc/quantitizer.h"

Image Quantitizer::encode(Image im, int bits_count) {
  Image low_pass_im = lowPassFilterImage(im);
  Image high_pass_im = highPassFilterImage(im);
  Image differentially_encoded_low_pass = encodeDifferentially(low_pass_im);
  Image quantified_high_pass = quantifyNonuniform(high_pass_im, bits_count);
  return quantified_high_pass;
}

Image Quantitizer::lowPassFilterImage(Image im) {
  Image low_pass_im = im;
  int low_pass_filter_sum = 0;
  for(int i = 0; i < low_pass_filter_matrix_.size(); i++) {
    for(auto val : low_pass_filter_matrix_.at(i)) {
      low_pass_filter_sum += val;
    }
  }

  for(int i = 0; i < im.height; i++) {
    for(int j = 0; j < im.width; j++) {
      int sum_b = 0;
      int sum_g = 0;
      int sum_r = 0;
      for(int k = -1; k < 1; k++) {
        for(int l = -1; l < 1; l++) {
          if(i + k < 0 || i + k > im.height || j + l < 0 || j + l > im.width) {
            continue;
          } else {
            sum_b += im.pixels.at(i + k).at(j+l).blue * low_pass_filter_matrix_.at(k + 1).at(l + 1);
            sum_g += im.pixels.at(i + k).at(j+l).green * low_pass_filter_matrix_.at(k + 1).at(l + 1);
            sum_r += im.pixels.at(i + k).at(j+l).red * low_pass_filter_matrix_.at(k + 1).at(l + 1);
          }
        }
      }
      sum_r /= low_pass_filter_sum;
      sum_g /= low_pass_filter_sum;
      sum_b /= low_pass_filter_sum;
      if(sum_b < 0)
        sum_b = 0;
      else if(sum_b > 255)
        sum_b = 255;
      if(sum_g < 0)
        sum_g = 0;
      else if(sum_g > 255)
        sum_g = 255;
      if(sum_r < 0)
        sum_r = 0;
      else if(sum_r > 255)
        sum_r = 255;
      low_pass_im.pixels.at(i).at(j) = {sum_r,
                                        sum_g,
                                        sum_b};
    }
  }
  return low_pass_im;
}

// TODO(Jakub Drzewiecki): Add % 256 to every addition
Image Quantitizer::highPassFilterImage(Image im) {
  Image high_pass_im = im;
  for(int i = 0; i < im.height; i++) {
    for(int j = 0; j < im.width; j++) {
      int sum_b = 0;
      int sum_g = 0;
      int sum_r = 0;
      for(int k = -1; k < 1; k++) {
        for(int l = -1; l < 1; l++) {
          if(i + k < 0 || i + k > im.height || j + l < 0 || j + l > im.width) {
            continue;
          } else {
            sum_b += im.pixels.at(i + k).at(j+l).blue * high_pass_filter_matrix_.at(k + 1).at(l + 1);
            sum_g += im.pixels.at(i + k).at(j+l).green * high_pass_filter_matrix_.at(k + 1).at(l + 1);
            sum_r += im.pixels.at(i + k).at(j+l).red * high_pass_filter_matrix_.at(k + 1).at(l + 1);
          }
        }
      }
      if(sum_b < 0)
        sum_b = 0;
      else if(sum_b > 255)
        sum_b = 255;
      if(sum_g < 0)
        sum_g = 0;
      else if(sum_g > 255)
        sum_g = 255;
      if(sum_r < 0)
        sum_r = 0;
      else if(sum_r > 255)
        sum_r = 255;
      high_pass_im.pixels.at(i).at(j) = {sum_r,
                                        sum_g,
                                        sum_b};
    }
  }
  return high_pass_im;
}

Image Quantitizer::encodeDifferentially(Image im) {
  Image new_im = im;
  for(int i = im.height - 1; i >= 0; i--) {
    for(int j = im.width - 1; j >= 0; j--) {
      if(i == 0 && j == 0)
        break;
      if(j == 0) {
        new_im.pixels.at(i).at(j) = im.pixels.at(i).at(j) - im.pixels.at(i-1).at(im.width - 1);
      } else {
        new_im.pixels.at(i).at(j) = im.pixels.at(i).at(j) - im.pixels.at(i).at(j-1);
      }
    }
  }
  return new_im;
}

Image Quantitizer::decodeDifferentially(Image im) {
  Image new_im = im;
  for(int i = 0; i < im.height; i++) {
    for(int j = 0; j < im.width; j++) {
      if(j + 1 == im.width && i == im.height - 1) {
        break;
      }
      if(j + 1 == im.width) {
        new_im.pixels.at(i+1).at(0) = new_im.pixels.at(i).at(j) + im.pixels.at(i+1).at(0);
      } else {
        new_im.pixels.at(i).at(j+1) = new_im.pixels.at(i).at(j) + im.pixels.at(i).at(j+1);
      }
    }
  }
  return new_im;
}

Image Quantitizer::quantifyNonuniform(Image im, int k) {
  long long int lvl = 1 << (k-1);
  std::unordered_map<int, int> red_bandwidth_dist;
  std::unordered_map<int, int> green_bandwidth_dist;
  std::unordered_map<int, int> blue_bandwidth_dist;
  for(int i = 0; i < 256; i++) {
    red_bandwidth_dist[i] = 0;
    green_bandwidth_dist[i] = 0;
    blue_bandwidth_dist[i] = 0;
  }
  for(auto row : im.pixels) {
    for(auto pix : row) {
      red_bandwidth_dist.at(pix.red)++;
      green_bandwidth_dist.at(pix.green)++;
      blue_bandwidth_dist.at(pix.blue)++;
    }
  }
  std::unordered_map<int, int> red_vals_mapping =
      limitIntervalsCount(red_bandwidth_dist, lvl);
  std::unordered_map<int, int> green_vals_mapping =
      limitIntervalsCount(green_bandwidth_dist, lvl);
  std::unordered_map<int, int> blue_vals_mapping =
      limitIntervalsCount(blue_bandwidth_dist, lvl);

  for(int i = 0; i < im.height; i++) {
    for(int j = 0; j < im.width; j++) {
      im.pixels.at(i).at(j).red = red_vals_mapping[im.pixels.at(i).at(j).red];
      im.pixels.at(i).at(j).green = red_vals_mapping[im.pixels.at(i).at(j).green];
      im.pixels.at(i).at(j).blue = red_vals_mapping[im.pixels.at(i).at(j).blue];
    }
  }

  return im;
}

std::unordered_map<int, int> Quantitizer::limitIntervalsCount(
    std::unordered_map<int,int> channel_distribution,
    long long int lvl) {
  std::vector<std::pair<std::pair<int, int>, int>> intervals;

  for(int i = 0; i < channel_distribution.size(); i++) {
    intervals.push_back({{i, i+1}, channel_distribution.at(i)});
  }
  while(intervals.size() > lvl) {
    int dist_min = std::numeric_limits<int>::max();
    int index;
    for(int i = 0; i < intervals.size(); i++) {
      auto set = intervals.at(i);
      int dist = set.second;
      if(dist < dist_min) {
        dist_min = dist;
        index = i;
      }
    }

    std::vector<std::pair<std::pair<int, int>, int>> new_intervals;
    if(index == 0) {
      for(int i = 1; i < intervals.size(); i++) {
        new_intervals.push_back(intervals.at(i));
      }
      new_intervals.at(0).first.first = intervals.at(0).first.first;
      new_intervals.at(0).second += intervals.at(0).second;
    } else if(index == intervals.size() - 1) {
      for(int i = 0; i < intervals.size() - 1; i++) {
        new_intervals.push_back(intervals.at(i));
      }
      new_intervals.at(index - 1).first.second = intervals.at(index).first.second;
      new_intervals.at(index - 1).second += intervals.at(index).second;
    } else {
      for(int i = 0; i < index; i++) {
        new_intervals.push_back(intervals.at(i));
      }
      for(int i = index + 1; i < intervals.size(); i++) {
        new_intervals.push_back(intervals.at(i));
      }
      if(new_intervals.at(index - 1).second > new_intervals.at(index).second) {
        new_intervals.at(index).first.first = new_intervals.at(index - 1).first.second;
        new_intervals.at(index).second += intervals.at(index).second;
      } else {
        new_intervals.at(index-1).first.second = new_intervals.at(index).first.first;
        new_intervals.at(index-1).second += intervals.at(index).second;
      }
    }
    intervals = new_intervals;
  }

  std::unordered_map<int, int> pixel_val_mapping;
  int j = 0;
  for(int i = 0; i < 256; i++) {
    if(i >= intervals[j].first.second) {
      j++;
    }
    pixel_val_mapping[i] = intervals[j].first.first;
  }

  return pixel_val_mapping;
}