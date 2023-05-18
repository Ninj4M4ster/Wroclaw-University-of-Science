#include <iostream>
#include <fstream>
#include <bitset>

/**
 * Algorithm for calculating 16 bit crc sum using arc algorithm.
 *
 * @param crc Current value of crc.
 * @param data
 * @return
 */
uint16_t crc16arc_bit(std::string & data) {
  uint16_t crc = 0;
  if (data.empty())
    return 0;
  for (char i : data) {
    crc ^= i;
    for (unsigned k = 0; k < 8; k++) {
      crc = crc & 1 ? (crc >> 1) ^ 0xa001 : crc >> 1;
    }
  }
  return crc;
}

/**
 * Method for parsing frame data with frame start sequence and crc sum.
 *
 * @param current_frame Frame to parse.
 * @return Formatted frame.
 */
std::string parse_frame(std::string current_frame) {
  // find crc sum
  int crc_sum = crc16arc_bit(current_frame);

  // convert crc sum to string
  std::string crc_string;
  uint16_t msb = 0x8000;
  for(int i = 0; i < 16; i++) {
    crc_string += ((crc_sum & msb) >> (15 - i)) + '0';
    msb >>= 1;
  }

  return "01111110" + current_frame + crc_string;
}

/**
 * Method for encoding bit stream from given file. It finds sequences with 6 '1' bits and inserts '0' after 5-th bit.
 *
 * @param file_ds File with bit stream.
 * @return Data parsed as frames.
 */
std::string encode(std::fstream & file_ds) {
  static constexpr auto max_frame_size = 200;
  int current_frame_size = 8;
  std::string all_data;
  int one_count = 0;
  std::string current_frame;
  char buffer[1] = {};
  // gather all bits from file
  while(file_ds.read(buffer, sizeof(char))) {
    current_frame += buffer[0];
    current_frame_size++;
    if(buffer[0] == '0') {
      one_count = 0;
    } else {  // buffer[0] == '1'
      one_count++;
      if(one_count == 5) {
        current_frame_size++;
        current_frame += '0';
        one_count = 0;
        if(current_frame_size == max_frame_size) {  // parse single frame and continue
          all_data += parse_frame(current_frame);
          current_frame = "";
          current_frame_size = 8;
        }
      }
    }
    if(current_frame_size == max_frame_size) {  // parse single frame and continue
      all_data += parse_frame(current_frame);
      current_frame = "";
      current_frame_size = 8;
    }
  }

  if(current_frame_size > 8) {
    all_data += parse_frame(current_frame);
  }

  return all_data;
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cout << "Podano nieprawidlowa ilosc argumentow.\n";
    return -1;
  }

  std::fstream f;
  f.open(argv[1]);
  std::string result = encode(f);
  f.close();

  f.open("W.txt", std::fstream::out);
  for(char c : result) {
    f << c;
  }
  f.close();
}