#include <iostream>
#include <fstream>
#include <bitset>

uint16_t crc16arc_bit(uint16_t crc, std::string & data) {
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

std::string encode(std::fstream & file_ds) {
  uint16_t crc_sum = 0;
  int one_count = 0;
  std::string result_string;
  char buffer[1] = {};
  // gather all bits from file
  while(file_ds.read(buffer, sizeof(char))) {
    if(buffer[0] == '0') {
      one_count = 0;
    } else {  // buffer[0] == '1'
      if(one_count == 5) {
        result_string += '0';
        one_count = 0;
      }
      one_count++;
    }
    result_string += buffer[0];
  }

  // find crc sum
  crc_sum = crc16arc_bit(crc_sum, result_string);

  // convert crc sum to string
  std::string crc_string;
  uint16_t msb = 0x8000;
  for(int i = 0; i < 16; i++) {
    crc_string += ((crc_sum & msb) >> (15 - i)) + '0';
    msb >>= 1;
  }

  return "01111110" +  result_string + crc_string + "01111110";
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
    std::cout << c;
    f << c;
  }
  std::cout << std::endl;
  f.close();
}