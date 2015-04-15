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

void BMP_data::open(const std::string& fname) {
  std::ifstream ifs(fname, std::ios::binary);
  std::ostringstream ost;
  ost << ifs.rdbuf();
  std::string bytes(ost.str());
  data = bytes;
}

void BMP_data::write(const std::string& fname) {
  std::ofstream ofs(fname, std::ios::binary);
  ofs << data;
}

// returns the offset at which the pixel array begins (The data after the BMP header info)
unsigned BMP_data::image_offset() const {
  std::string bytes = data.substr(0xa, 4);
  int offset = bytes_to_int(bytes);
  return offset;
}

unsigned BMP_data::bits_per_pixel() const {
  std::string bytes = data.substr(0x1c, 2);
  int bpp = bytes_to_int(bytes);
  return bpp;
}

int BMP_data::width() const {
  std::string bytes = data.substr(0x12, 4);
  int w = bytes_to_int(bytes);
  return w;
}

int BMP_data::height() const {
  std::string bytes = data.substr(0x16, 4);
  int h = bytes_to_int(bytes);
  return h;
}

unsigned BMP_data::num_color_planes() const {
  std::string bytes = data.substr(0x1a, 2);
  int cp = bytes_to_int(bytes);
  return cp;
}

bool BMP_data::is_valid() const {
  std::string validation = data.substr(0, 2);
  return validation == "BM" && num_color_planes() == 1;
}

void BMP_data::mask_set_byte(int index, unsigned mask) {
  unsigned byte = data[index];
  byte |= mask;
  data[index] = byte;
  return;
}

void BMP_data::mask_unset_byte(int index, unsigned mask) {
  return;
}
}
}
