#include <cstdint>
#include "extracting_agent.hh"

Extracting_agent::Extracting_agent(const std::string& inbmp_fname)
    : inbmp(inbmp_fname) {}

std::string Extracting_agent::extract() const { 
  std::string msg;
  std::vector<bool> msg_bits;

  int width = inbmp.get_width();
  int height = inbmp.get_height();
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      std::vector<bool> bits = extract_bits_from_pixel(j, i);
      msg_bits.insert(msg_bits.end(), bits.begin(), bits.end());
      if (is_last_byte_terminate(msg_bits)) {
        msg_bits.erase(msg_bits.end() - 8, msg_bits.end());
        return bits_to_string(msg_bits);
      }
    }
  }
  return msg;
}

std::string Extracting_agent::bits_to_string(const std::vector<bool>& bits) const {
  std::string str;
  for (int i = 0; (unsigned)i < bits.size(); i += 8) {
    uint8_t c = 0;
    for (int j = 7; j >= 0; --j) {
      int index = i + 7 - j;
      c |= (bits[index] << j);
    }
    str += (char)c;
  }
  return str;
}

std::vector<bool> Extracting_agent::extract_bits_from_pixel(int x, int y) const {
  std::vector<bool> bits;
  unsigned num_bits = inbmp.get_bpp() / 8;
  unsigned pixel = inbmp.get_pixel(x, y);
  for (int i = 0; i < num_bits; ++i) {
    unsigned bit = 0;
    bit |= (pixel >> (i * 8)) & 0x1;
    bits.push_back(bit && 0x1);
  }
  return bits;
}

bool Extracting_agent::is_last_byte_terminate(const std::vector<bool>& bits) const {
  int consecutive_zeroes = 0;
  unsigned size = bits.size();
  for (int i = size; i>= 0 && i > size - 8; --i) {
    if (!bits[i]) {
      ++consecutive_zeroes;
    } else {
      consecutive_zeroes = 0;
    }
  }
  return consecutive_zeroes == 8;
}
