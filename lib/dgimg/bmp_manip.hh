#ifndef BMP_MANIP_HH
#define BMP_MANIP_HH

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>

typedef std::string bmp_t;


static int bytes_to_int(const std::string& bytes) {
  char* dword = new char[4];
  memcpy(dword, bytes.c_str(), 4);
  int ret;
  if (bytes.length() == 2) {
    short temp = *(short*)dword;
    ret = temp;
  } else {
    ret = *(int*)dword;
  }
  delete dword;
  return ret;
}

bmp_t open_bmp(const std::string& fname) {
  std::ifstream ifs(fname, std::ios::binary);
  std::ostringstream ost;
  ost << ifs.rdbuf();
  bmp_t bmp(ost.str());
  return bmp;
}

// returns the offset at which the pixel array begins (The data after the BMP header info)
unsigned bmp_image_offset(const bmp_t& bmp) {
  std::string bytes = bmp.substr(0xa, 4);
  int offset = bytes_to_int(bytes);
  return offset;
}

unsigned bmp_bits_per_pixel(const bmp_t& bmp) {
  std::string bytes = bmp.substr(0x1c, 2);
  int bpp = bytes_to_int(bytes);
  return bpp;
}

int bmp_width(const bmp_t& bmp) {
  std::string bytes = bmp.substr(0x12, 4);
  int w = bytes_to_int(bytes);
  return w;
}

int bmp_height(const bmp_t& bmp) {
  std::string bytes = bmp.substr(0x16, 4);
  int h = bytes_to_int(bytes);
  return h;
}

bool is_bmp_valid(const bmp_t& bmp) {
  std::string validation = bmp.substr(0, 2);
  return validation == "BM";
}

#endif // BMP_MANIP_HH
