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

//// friend non-member operators
std::ostream& operator<<(std::ostream& os, const DG::Image::BMP& bmp) {
  return os;
}

std::istream& operator>>(std::istream& is, DG::Image::BMP& bmp) {
  return is;
}

}
}
