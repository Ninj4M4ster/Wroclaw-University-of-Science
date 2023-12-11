#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST5_QUANTITIZER_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST5_QUANTITIZER_H_

#include "image.h"

class Quantitizer {
 public:
  Quantitizer(Image image, int level);
  void quantify(double epsilon);

 private:
  Image im_;
  size_t lvl_;

  std::vector<Pixel> Y_;
  std::vector<std::vector<std::pair<int, int>>> pixels_coords_;

  void splitImage(double epsilon);
  Pixel pixelPerturbation(Pixel p, int perturbation);
  Pixel avg_vector(std::vector<std::vector<Pixel>>& pixels);
  Pixel avg_vector(std::vector<Pixel>& pixels);
  size_t distance(Pixel a, Pixel b);
  double calculateDistortion(std::vector<std::vector<Pixel>> V);
};

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST5_QUANTITIZER_H_
