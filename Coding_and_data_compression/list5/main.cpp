#include <fstream>
#include "quantitizer.cpp"

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

int main() {
  std::string input_photo_name = "data/example0.tga";
  std::string output_photo_name = "result.tga";
  int q_level = 8;
  Image image = readPhoto(input_photo_name);
  Quantitizer quantitizer(image, q_level);
  quantitizer.quantify(0.001);
  quantitizer.outputImage(input_photo_name, output_photo_name);

  std::cout << "Result image distortion: " << quantitizer.getResultDistortion() << "\n";
  std::cout << "Signal to noise ratio: " << quantitizer.signalNoiseRatio() << "\n";
}