#include <cstdint>
#include "abstract_extracting_agent.hh"

std::string Abstract_extracting_agent::bits_to_string(const std::vector<bool>& bits) const {
  std::string str;
  for (int i = 0; (unsigned)i < bits.size(); i += 8) {
    uint8_t c = 0;
    for (int j = 7; j >= 0; --j) {
      int index = i + 7 - j;
      c |= (bits[index] << j);
    }
    if (c == 0x0) {
      return str;
    }
    str += (char)c;
  }
  return str;
}

bool Abstract_extracting_agent::is_last_byte_terminate(const std::vector<bool>& bits) const {
  int consecutive_zeroes = 0;
  int start = bits.size();
  int mod = start % 8;
  start -= mod;
  for (int i = start; i>= 0 && i > start - 8; --i) {
    if (!bits[i]) {
      ++consecutive_zeroes;
    } else {
      consecutive_zeroes = 0;
    }
  }
  return consecutive_zeroes == 8;
}
