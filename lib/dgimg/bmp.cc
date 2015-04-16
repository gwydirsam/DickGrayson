#include <iostream>
#include <cstdint>
#include <limits>
#include <cmath>
#include <iostream>
#include "bmp.hh"

namespace DG {
namespace Image {

void BMP::open(const std::string& fname) {
  std::ifstream ifs(fname, std::ios::binary);
  ifs >> data;
}

void BMP::write(const std::string& fname) {
  std::ofstream ofs(fname, std::ios::binary | std::ios::trunc);
  ofs << data;
}

void BMP::byte_set_mask(int index, unsigned mask) {
  unsigned byte = data.byte_array[index + data.image_offset()];
  byte |= mask;
  data.byte_array[index + data.image_offset()] = byte;
  return;
}

void BMP::byte_unset_mask(int index, unsigned mask) {
  unsigned byte = data.byte_array[index + data.image_offset()];
  byte &= ~mask;
  data.byte_array[index + data.image_offset()] = byte;
  return;
}

unsigned BMP::max_pixel_value() const {
  int bpp = data.bits_per_pixel();
  int width = data.width();
  int height = data.height();
  int num_subpixels = bpp / 8; // we support 8-bit and 24-bit
  int row_size = num_subpixels * width; // take padding into account
  int mod = row_size % 4;
  if (mod) {
    row_size += mod;
  }
  const std::string& pixel_array = data.get_pixel_array();

  int i = 0;
  int current_row = 1;
  unsigned max = std::numeric_limits<unsigned>::min();

  int z = 0;
  while (i < pixel_array.size()) {
    if (i > (current_row) * width * num_subpixels) {
      ++current_row;
      i += mod;
    }
    uint32_t pixel_value = 0;
    for (int j = 0; j < num_subpixels; ++j) {
      ++z;
      uint8_t subpixel_value = pixel_array[i + j];
      uint8_t shift = (num_subpixels - j - 1) * 8;
      pixel_value |= subpixel_value << shift;
    }
    if (pixel_value > max) {
      max = pixel_value;
    }
    i += num_subpixels;
  }
  return max;
}

//// friend non-member operators
std::ostream& operator<<(std::ostream& os, const DG::Image::BMP& bmp) {
  return os;
}

std::istream& operator>>(std::istream& is, DG::Image::BMP& bmp) {
  return is;
}

}
}
