#include "bmp_data.hh"

namespace DG {
namespace Image {

int BMP_data::bytes_to_int(const std::string& bytes) const {
  int ret;
  if (bytes.length() == 2) {
    short temp = *(short*)bytes.c_str();
    ret = temp;
  } else {
    ret = *(int*)bytes.c_str();
  }
  return ret;
}

// open
std::istream& operator>>(std::istream& is, BMP_data& bmp) {
  std::ostringstream ost;
  ost << is.rdbuf();
  std::string bytes(ost.str());
  bmp.byte_array = bytes;
  bmp.pixel_array =
      bmp.byte_array.substr(bmp.image_offset(), bmp.pixel_array_size());
  return is;
}

// write
std::ostream& operator<<(std::ostream& os, const BMP_data& bmp) {
  os << bmp.byte_array;
  return os;
}

// returns the offset at which the pixel array begins (The data after the BMP
// header info)
unsigned BMP_data::image_offset() const {
  std::string bytes = byte_array.substr(0xa, 4);
  int offset = bytes_to_int(bytes);
  return offset;
}

unsigned BMP_data::bits_per_pixel() const {
  std::string bytes = byte_array.substr(0x1c, 2);
  int bpp = bytes_to_int(bytes);
  return bpp;
}

int BMP_data::width() const {
  std::string bytes = byte_array.substr(0x12, 4);
  int w = bytes_to_int(bytes);
  return w;
}

int BMP_data::height() const {
  std::string bytes = byte_array.substr(0x16, 4);
  int h = bytes_to_int(bytes);
  return h;
}

unsigned BMP_data::pixel_array_size() const {
  std::string bytes = byte_array.substr(0x22, 4);
  int pas = bytes_to_int(bytes);
  return pas;
}

unsigned BMP_data::num_color_planes() const {
  std::string bytes = byte_array.substr(0x1a, 2);
  int cp = bytes_to_int(bytes);
  return cp;
}

bool BMP_data::is_valid() const {
  std::string validation = byte_array.substr(0, 2);
  return validation == "BM" && num_color_planes() == 1;
}
}
}
