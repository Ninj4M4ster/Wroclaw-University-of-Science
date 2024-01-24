#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST6_INC_QUANTITIZER_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST6_INC_QUANTITIZER_H_

#include "image.h"

class Quantitizer {
 public:
  Image encode(Image im, int bits_count);

 private:
  std::vector<Pixel> lowPassFilterImage(Image im);
  std::vector<Pixel> highPassFilterImage(Image im);

  std::vector<Pixel> encodeDifferentially(std::vector<Pixel> pixels);
  std::vector<Pixel> encodeDifferentiallyMinimizingError(std::vector<Pixel> pixels,
                                                         std::vector<std::vector<int>> quant_ranges);

  std::vector<std::vector<int>> quantify(std::vector<Pixel> input, int k);
  std::vector<int> quantifySingleChannel(std::vector<int> single_channel, int lvl);

  std::vector<Pixel> reconstructImageFromQuantizationMap(std::vector<std::vector<int>> ranges,
                                                         std::vector<Pixel> input);

  void signalNoiseRatio(Image im1, Image im2);
  double minSquareError(Image im1, Image im2);
  int distance(Pixel a, Pixel b);
  void minSquareChannelsError(Image im1, Image im2);
  int findIndex(int val, std::vector<int> range);

  Image sumImages(std::vector<Pixel> y, std::vector<Pixel> z, Image original_im);
};

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST6_INC_QUANTITIZER_H_
