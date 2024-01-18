#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST6_INC_IMAGE_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST6_INC_IMAGE_H_

#include <iostream>
#include <vector>

typedef struct pixel {
  int red = 0;
  int green = 0;
  int blue = 0;
} Pixel;

Pixel operator+(Pixel p1, Pixel p2) {
  return {(p1.red + p2.red), (p1.green + p2.green), (p1.blue + p2.blue)};
}

Pixel operator-(Pixel p1, Pixel p2) {
  Pixel res = {p1.red - p2.red, p1.green - p2.green, p1.blue - p2.blue};
  return res;
}

Pixel operator/(Pixel p1, int div) {
  p1.red /= div;
  p1.green /= div;
  p1.blue /= div;
  return p1;
}

typedef struct image {
  size_t width = 0;
  size_t height = 0;
  std::vector<std::vector<Pixel>> pixels;
} Image;


#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST6_INC_IMAGE_H_
