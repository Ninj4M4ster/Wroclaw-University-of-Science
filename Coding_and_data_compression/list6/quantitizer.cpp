#include "inc/quantitizer.h"

Image Quantitizer::encode(Image im, int bits_count) {
  return lowPassFilterImage(im);
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