#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <cmath>

typedef struct pixel {
  int red = 0;
  int green = 0;
  int blue = 0;
} Pixel;

Pixel operator+(Pixel p1, Pixel p2) {
  return {(p1.red + p2.red) % 256, (p1.green + p2.green) % 256, (p1.blue + p2.blue) % 256};
}

Pixel operator-(Pixel p1, Pixel p2) {
  Pixel res = {p1.red - p2.red, p1.green - p2.green, p1.blue - p2.blue};
  while(res.red < 0)
    res.red += 256;
  while(res.green < 0)
    res.green += 256;
  while(res.blue < 0)
    res.blue += 256;
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

Image readPhoto(std::string file_name) {
  std::fstream f;
  f.open(file_name, std::ios::in | std::ios::binary);
  if(f.fail()) {
    throw std::runtime_error("Could not open file " + file_name);
  }
  Image image;
  for(int i = 0; i < 12; i++) {
    f.get();
  }
  image.width |= f.get() | (static_cast<size_t>(f.get()) << 8);
  image.height |= f.get() | (static_cast<size_t>(f.get()) << 8);
  for(int i = 0; i < 2; i++) {
    f.get();
  }
  image.pixels = std::vector<std::vector<Pixel>>(image.height, std::vector<Pixel>(image.width));
  for(int i = image.height - 1; i >= 0; i--) {
    for(int j = 0; j < image.width; j++) {
      int blue = f.get();
      int green = f.get();
      int red = f.get();
      image.pixels.at(i).at(j) = {red, green, blue};
    }
  }

  f.close();

  return image;
}

int findBestValue(int N_color, int W_color, int NW_color) {
  if(NW_color >= std::max(W_color, N_color)) {
    return std::max(W_color, N_color);
  } else if(NW_color <= std::min(W_color, N_color)) {
    return std::min(N_color, W_color);
  }
  int res = W_color + N_color - NW_color;
  res %= 256;
  while(res < 0) {
    res += 256;
  }
  return res;
}

Pixel fromNewStandard(Pixel& N, Pixel& W, Pixel& NW) {
  Pixel result;
  result.red = findBestValue(N.red, W.red, NW.red);
  result.blue = findBestValue(N.blue, W.blue, NW.blue);
  result.green = findBestValue(N.green, W.green, NW.green);
  return result;
}

std::vector<Image> generateJpegLs(Image & image) {
  Image res_im;
  res_im.width = image.width;
  res_im.height = image.height;
  res_im.pixels = std::vector<std::vector<Pixel>>(res_im.height, std::vector<Pixel>(res_im.width));
  std::vector<Image> results(8, res_im);
  for(int i = 0; i < res_im.height; i++) {
    for(int j = 0; j < res_im.width; j++) {
      Pixel N = i == 0 ? Pixel{0,0,0} : image.pixels.at(i-1).at(j);
      Pixel W = j == 0 ? Pixel{0,0,0} : image.pixels.at(i).at(j-1);
      Pixel NW = (j == 0 || i == 0) ? Pixel{0,0,0} : image.pixels.at(i-1).at(j-1);

      results.at(0).pixels.at(i).at(j) = image.pixels.at(i).at(j) - W;
      results.at(1).pixels.at(i).at(j) = image.pixels.at(i).at(j) - N;
      results.at(2).pixels.at(i).at(j) = image.pixels.at(i).at(j) - NW;
      results.at(3).pixels.at(i).at(j) = image.pixels.at(i).at(j) - (N + W - NW);
      results.at(4).pixels.at(i).at(j) = image.pixels.at(i).at(j) - (N + (W - NW) / 2);
      results.at(5).pixels.at(i).at(j) = image.pixels.at(i).at(j) - (W + (N - NW) / 2);
      results.at(6).pixels.at(i).at(j) = image.pixels.at(i).at(j) - ((N + W) / 2);
      results.at(7).pixels.at(i).at(j) = image.pixels.at(i).at(j) - fromNewStandard(N, W, NW);
    }
  }
  return results;
}

std::vector<double> calculateEntropies(Image & im) {
  std::unordered_map<int, size_t> red_freq;
  size_t red_freq_sum = 0;
  std::unordered_map<int, size_t> blue_freq;
  size_t blue_freq_sum = 0;
  std::unordered_map<int, size_t> green_freq;
  size_t green_freq_sum = 0;
  std::vector<std::vector<std::vector<size_t>>> joint_freq(256, std::vector<std::vector<size_t>>(256, std::vector<size_t>(256, 0)));
  for(int i = 0; i < 256; i++) {
    red_freq[i] = 0;
    blue_freq[i] = 0;
    green_freq[i] = 0;
  }
  for(auto & pix_row : im.pixels) {
    for(auto & pix : pix_row) {
      red_freq[pix.red]++;
      red_freq_sum++;
      blue_freq[pix.blue]++;
      blue_freq_sum++;
      green_freq[pix.green]++;
      green_freq_sum++;
      joint_freq.at(pix.red).at(pix.green).at(pix.blue)++;
    }
  }
  size_t joint_freq_sum = red_freq_sum + blue_freq_sum + green_freq_sum;

  std::vector<double> results;
  double entropy = 0.0;
  double red_entropy = 0.0;
  double blue_entropy = 0.0;
  double green_entropy = 0.0;

  for(int i = 0; i < 256; i++) {
    double p_red = static_cast<double>(red_freq[i]) / static_cast<double>(red_freq_sum);
    double p_green = static_cast<double>(green_freq[i]) / static_cast<double>(green_freq_sum);
    double p_blue = static_cast<double>(blue_freq[i]) / static_cast<double>(blue_freq_sum);
    if(p_red != 0.0) {
      red_entropy -= p_red * std::log2(p_red);
    }
    if(p_green != 0.0) {
      green_entropy -= p_green * std::log2(p_green);
    }
    if(p_blue != 0.0) {
      blue_entropy -= p_blue * std::log2(p_blue);
    }
  }

  for(int i = 0; i < 256; i++) {
    for(int j = 0; j < 256; j++) {
      for(int k = 0; k < 256; k++) {
        double p = static_cast<double>(joint_freq.at(i).at(j).at(k)) / static_cast<double>(joint_freq_sum/3);
        if(p != 0.0) {
          entropy -= p * std::log2(p);
        }
      }
    }
  }

  results = {entropy, red_entropy, green_entropy, blue_entropy};
  return results;
}

int main() {
  std::vector<std::string> image_names{"data/example0.tga",
                                       "data/example1.tga",
                                       "data/example2.tga",
                                       "data/example3.tga"};
  std::vector<std::string> methods{"W", "N", "NW", "N+W-NW", "N+(W-NW)/2", "W+(N-NW)/2", "(N+W)/2", "New standard"};
  std::vector<std::string> entropy_orders{"image", "red", "green", "blue"};
  for(auto f_name : image_names) {
    Image im = readPhoto(f_name);
    std::vector<Image> compressed_images = generateJpegLs(im);
    std::vector<double> entropies = calculateEntropies(im);
    std::cout << "Image name: " << f_name << std::endl;
    for(int i = 0; i < entropies.size(); i++) {
      std::cout << entropy_orders.at(i) << " entropy: " << entropies.at(i) << std::endl;
    }
    std::cout << std::endl;
    double min_red = std::numeric_limits<double>::max();
    double min_blue = std::numeric_limits<double>::max();
    double min_green = std::numeric_limits<double>::max();
    double min_full = std::numeric_limits<double>::max();
    int min_red_id = 0;
    int min_blue_id = 0;
    int min_green_id = 0;
    int min_full_id = 0;
    for(int i = 0; i < compressed_images.size(); i++) {
      entropies = calculateEntropies(compressed_images.at(i));
      std::cout << methods.at(i) << std::endl;
      for(int j = 0; j < entropies.size(); j++) {
        std::cout << entropy_orders.at(j) << " entropy: " << entropies.at(j) << std::endl;
      }
      if(entropies.at(0) < min_full) {
        min_full = entropies.at(0);
        min_full_id = i;
      }
      if(entropies.at(1) < min_red) {
        min_red = entropies.at(1);
        min_red_id = i;
      }
      if(entropies.at(2) < min_green) {
        min_green = entropies.at(2);
        min_green_id = i;
      }
      if(entropies.at(3) < min_blue) {
        min_blue = entropies.at(3);
        min_blue_id = i;
      }
      std::cout << "\n";
    }
    std::cout << "Best results\n";
    std::cout << "Image: " << methods.at(min_full_id) << ", " << min_full << std::endl;
    std::cout << "Red: " << methods.at(min_red_id) << ", " << min_red << std::endl;
    std::cout << "Green: " << methods.at(min_green_id) << ", " << min_green << std::endl;
    std::cout << "Blue: " << methods.at(min_blue_id) << ", " << min_blue << std::endl;
    std::cout << "\n\n";
  }
}