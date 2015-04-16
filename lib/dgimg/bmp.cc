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

unsigned BMP::get_pixel(int x, int y) const {
  const std::string& pixel_array = data.get_pixel_array();
  int bpp = data.bits_per_pixel();
  int width = data.width();
  int height = data.height();
  int num_subpixels = bpp / 8;
  int row_size = num_subpixels * width;
  int num_row_padding_bytes = row_size % 4;

  int pixel_offset = (x + y * height) * num_subpixels;
  pixel_offset += pixel_offset / (row_size + 1) * num_row_padding_bytes;

  uint32_t pixel_value = 0;
  for (int i = 0; i < num_subpixels; ++i) {
    uint8_t subpixel_value = pixel_array[pixel_offset + i];
    uint8_t shift = (num_subpixels - i - 1) * 8;
    pixel_value |= subpixel_value << shift;
  }
  return pixel_value;
}

unsigned BMP::max_pixel_value() const {
  unsigned max = std::numeric_limits<unsigned>::min();
  int width = data.width();
  int height = data.height();
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < height; ++j) {
      unsigned pixel_value = get_pixel(i, j);
      if (pixel_value > max) {
        max = pixel_value;
      }
    }
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
