#ifndef WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST6_INC_QUANTITIZER_H_
#define WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST6_INC_QUANTITIZER_H_

#include "image.h"

class Quantitizer {
 public:
  Image encode(Image im, int bits_count);
  Image decode(Image im, int bits_count);

 private:
  std::vector<std::vector<int>> low_pass_filter_matrix_ {
      {1, 1, 1},
      {1, 4, 1},
      {1, 1, 1}
  };
  std::vector<std::vector<int>> high_pass_filter_matrix_ {
      {0, -1, 0},
      {-1, 4, -1},
      {0, -1, 0}
  };

  Image lowPassFilterImage(Image im);
  Image highPassFilterImage(Image im);

  Image encodeDifferentially(Image im);
  Image decodeDifferentially(Image im);

  Image quantifyNonuniform(Image im, int k);
  std::unordered_map<int, int> limitIntervalsCount(
      std::unordered_map<int, int> channel_distribution,
      long long int lvl);

};

#endif //WROCLAW_UNIVERSITY_OF_SCIENCE_CODING_AND_DATA_COMPRESSION_LIST6_INC_QUANTITIZER_H_
