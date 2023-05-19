#include <iostream>
#include <fstream>
#include <string>

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
 * Method for checking crc of the frame with the one calculated using data of this frame.
 *
 * @param data Frame to be checked.
 * @param last_frame Was this the last given frame?
 * @return Is the crc sum correct?
 */
bool check_crc(std::string & data, bool last_frame) {
  std::string frame_data;
  std::string frame_crc;
  int index = 0;
  // gather frame data and crc data
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

  uint16_t calculated_crc = crc16arc_bit(frame_data);
  // convert crc sum to string
  std::string calculated_crc_string;
  uint16_t msb = 0x8000;
  for(int i = 0; i < 16; i++) {
    calculated_crc_string += ((calculated_crc & msb) >> (15 - i)) + '0';
    msb >>= 1;
  }

  return calculated_crc_string == frame_crc;
}

/**
 * Method for extracting data from given frame.
 *
 * @param data Frame.
 * @param last_frame Was this the last frame in the flow?
 * @return Data extracted from frame.
 */
std::string extract_data(std::string & data, bool last_frame) {
  int frame_end_offset = 0;
  if(!last_frame)
    frame_end_offset = 8;
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

/**
 * Extract data from frame without crc field.
 *
 * @param frame Frame data.
 * @return Frame data without crc.
 */
std::string extract_no_crc(std::string frame) {
  std::string final;
  for(int i = 0; i < frame.length() - 16; i++) {
    final += frame[i];
  }
  return final;
}

/**
 * Method for decoding frames from given file.
 * It finds frame start sequence and checks crc sum of every frame.
 * After correct crc sum it deletes inserted '0' bits.
 *
 * @param file_ds File to extract bit stream.
 * @return Reformatted data.
 */
std::string decode(std::fstream & file_ds) {
  bool last_frame_incorrect = false;
  int current_frame_size = 0;
  int one_count = 0;
  std::string current_frame;
  char buffer[1] = {};
  std::string all_data;
  // gather all bits from file
  while(file_ds.read(buffer, sizeof(char))) {
    current_frame += buffer[0];
    current_frame_size++;
    if(buffer[0] == '0') {
      if(one_count == 6) {
        // frame start
        if(current_frame_size == 8 || last_frame_incorrect) {
          last_frame_incorrect = false;
          current_frame_size = 0;
          current_frame = "";
        } else {  // parse frame and start new frame
          std::string new_frame = extract_data(current_frame, false);
          if(!check_crc(new_frame, false)) {
            last_frame_incorrect = true;
            current_frame = "";
            std::cout << "Otrzymano ramke z niepoprawnym polem crc\n";
          } else {
            all_data += extract_no_crc(new_frame);
            current_frame = "";
          }
        }
      }
      one_count = 0;
    } else {  // buffer[0] == '1'
      if(one_count == 6) {  // TODO: Change for waiting for new frame
        last_frame_incorrect = true;
        current_frame = "";
        std::cout << "Otrzymano niepoprawna ramke (ciag 7 jedynek).\n";
        one_count = 0;
      } else {
        one_count++;
      }
    }
  }
  if(current_frame.length() > 16 && !last_frame_incorrect) {
    std::string new_frame = extract_data(current_frame, true);
    if (!check_crc(new_frame, true)) {
      std::cout << "Otrzymano ramke z niepoprawnym polem crc\n";
    } else {
      all_data += extract_no_crc(new_frame);
    }
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

  f.open("X.txt", std::fstream::out);
  for(char c : result) {
    f << c;
  }
  f.close();
}