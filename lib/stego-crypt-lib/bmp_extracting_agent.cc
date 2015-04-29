#include "bmp_extracting_agent.hh"

std::string BMP_extracting_agent::extract() const {
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

std::vector<bool> BMP_extracting_agent::extract_bits_from_pixel(int x, int y) const {
  std::vector<bool> bits;
  unsigned num_bits = inbmp.get_bpp() / 8;
  unsigned pixel = inbmp.get_pixel(x, y);
  for (unsigned i = 0; i < num_bits; ++i) {
    unsigned bit = 0;
    bit |= (pixel >> (i * 8)) & 0x1u;
    bits.push_back(bit == 0x1u);
  }
  return bits;
}
