#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST6_INC_QUANTITIZER_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST6_INC_QUANTITIZER_H_

#include "image.h"

class Quantitizer {
 public:
  Image encode(Image im, int bits_count);

 private:
  std::vector<Pixel> putToSingleVector(std::vector<std::vector<Pixel>> pixels);

  std::vector<Pixel> lowPassFilterImage(Image im);
  std::vector<Pixel> highPassFilterImage(Image im);

  std::vector<Pixel> encodeDifferentially(std::vector<Pixel> pixels);
  std::vector<Pixel> encodeDifferentiallyMinimizingError(std::vector<Pixel> pixels,
                                                         std::vector<std::pair<int, Pixel>> quantization_map);

  std::vector<std::pair<int, Pixel>> quantifyNonuniform(std::vector<Pixel> input, int k);
  std::vector<std::pair<int, Pixel>> splitImage(double epsilon, int lvl, std::vector<Pixel> input, std::vector<Pixel> Y);
  Pixel avg_vector(std::vector<Pixel> pixels);
  Pixel pixelPerturbation(Pixel p, int perturbation);
  double calculateDistortion(std::vector<std::vector<Pixel>> V, std::vector<Pixel> Y, int size);

  std::vector<Pixel> reconstructImageFromQuantizationMap(std::vector<std::pair<int, Pixel>> map, std::vector<Pixel> input);

  void signalNoiseRatio(Image im1, Image im2);
  double minSquareError(Image im1, Image im2);
  int distance(Pixel a, Pixel b);
  void minSquareChannelsError(Image im1, Image im2);

  Image sumImages(std::vector<Pixel> y, std::vector<Pixel> z, Image original_im);
};

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST6_INC_QUANTITIZER_H_
