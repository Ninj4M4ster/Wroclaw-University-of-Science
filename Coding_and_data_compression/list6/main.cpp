#include "inc/image.h"
#include "quantitizer.cpp"
#include <fstream>

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

void outputPhoto(std::string output_file_name, std::string input_file_name, Image & photo) {
  std::fstream f, f_out;
  f.open(input_file_name, std::ios::in | std::ios::binary);
  f_out.open(output_file_name, std::ios::out | std::ios::binary);
  if(f.fail()) {
    throw std::runtime_error("Could not open file " + input_file_name);
  }
  if(f_out.fail()) {
    throw std::runtime_error("Could not open file " + output_file_name);
  }

  for(int i = 0; i < 18; i++) {
    f_out.put(f.get());
  }

  for(int i = photo.height - 1; i >= 0; i--) {
    for(int j = 0; j < photo.width; j++) {
      f_out.put(photo.pixels.at(i).at(j).blue);
      f_out.put(photo.pixels.at(i).at(j).green);
      f_out.put(photo.pixels.at(i).at(j).red);
    }
  }

  int data = f.get();
  while(!f.eof()) {
    f_out.put(data);
    data = f.get();
  }

  f_out.close();
  f.close();
}

int main() {
  Image ph = readPhoto("data/example3.tga");
  Quantitizer quantitizer;
  auto diff_and_quant = quantitizer.encode(ph, 4);
  outputPhoto("res.tga", "data/example3.tga", diff_and_quant);
}