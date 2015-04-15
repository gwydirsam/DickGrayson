#include "bmp_data.hh"

namespace DG {
namespace Image {

int BMP_data::bytes_to_int(const std::string& bytes) const {
  return 0;
}

void BMP_data::open(const std::string& fname) {
}

// returns the offset at which the pixel array begins (The data after the BMP header info)
unsigned BMP_data::image_offset() const {
  return 0;
}

unsigned BMP_data::bits_per_pixel() const {
  return 0;
}

int BMP_data::width() const {
  return 0;
}

int BMP_data::height() const {
  return 0;
}

bool BMP_data::is_valid() const {
  return false;
}
}
}
