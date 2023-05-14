#include <iostream>
#include <fstream>
#include <string>

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

bool check_crc(std::string & data, bool last_frame) {
  std::string frame_data;
  std::string frame_crc;
  int index = 0;
  if(!last_frame) {
    for (; index < data.length() - 24; index++) {
      frame_data += data[index];
    }
    for (; index < data.length() - 8; index++) {
      frame_crc += data[index];
    }
  } else {
    for (; index < data.length() - 16; index++) {
      frame_data += data[index];
    }
    for (; index < data.length(); index++) {
      frame_crc += data[index];
    }
  }

  uint16_t calculated_crc = crc16arc_bit(0, frame_data);
  // convert crc sum to string
  std::string calculated_crc_string;
  uint16_t msb = 0x8000;
  for(int i = 0; i < 16; i++) {
    calculated_crc_string += ((calculated_crc & msb) >> (15 - i)) + '0';
    msb >>= 1;
  }

  std::cout << "Got: " << frame_crc << std::endl;
  std::cout << "Calcualted: " << calculated_crc_string << std::endl;

  return calculated_crc_string == frame_crc;
}

std::string parse_data(std::string & data, bool last_frame) {
  int frame_end_offset;
  if(last_frame)
    frame_end_offset = 16;
  else
    frame_end_offset = 24;
  int one_count = 0;
  int current_frame_size = 0;
  std::string converted_frame;
  while(current_frame_size < data.length() - frame_end_offset) {
    if(data[current_frame_size] == '0') {
      if(one_count == 5) {
        current_frame_size++;
        one_count = 0;
        continue;
      }
      one_count = 0;
    } else {
      one_count++;
    }
    converted_frame += data[current_frame_size];
    current_frame_size++;
  }
  return converted_frame;
}

std::string decode(std::fstream & file_ds) {
  int current_frame_size = 0;
  int one_count = 0;
  std::string current_frame;
  char buffer[1] = {};
  std::string all_data;
  // gather all bits from file
  while(file_ds.read(buffer, sizeof(char))) {
    current_frame += buffer[0];
    std::cout << current_frame << std::endl;
    current_frame_size++;
    if(buffer[0] == '0') {
      if(one_count == 6) {
        if(current_frame_size == 8) {  // first frame
          current_frame_size = 0;
          current_frame = "";
        } else {  // parse frame and start new frame
          if(!check_crc(current_frame, false)) {
            throw std::runtime_error("Pole crc jest niepoprawne.");
          }
          all_data += parse_data(current_frame, false);
          current_frame = "";
        }
      }
      one_count = 0;
    } else {  // buffer[0] == '1'
      if(one_count == 6) {  // TODO: Change for waiting for new frame
        throw std::runtime_error("Otrzymano niepoprawne dane (ciag 7 jedynek).");
      }
      one_count++;
    }
  }
  if(current_frame.length() > 16) {
    if (!check_crc(current_frame, true)) {
      throw std::runtime_error("Pole crc jest niepoprawne.");
    }
    all_data += parse_data(current_frame, true);
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
  std::string result = decode(f);
  f.close();

  std::cout << result << std::endl;

  f.open("X.txt", std::fstream::out);
  for(char c : result) {
    std::cout << c;
    f << c;
  }
  std::cout << std::endl;
  f.close();
}