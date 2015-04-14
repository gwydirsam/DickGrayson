#ifndef BMP_MANIP_HH
#define BMP_MANIP_HH

#include <string>
#include <iostream>

typedef std::string bmp_t;

bmp_t open_bmp(const std::string& fname) {
  return bmp_t();
}

bool is_bmp_valid(const bmp_t& bmp) {
  std::string validation = bmp.substr(0, 2);
  return validation == "BM";
}

#endif // BMP_MANIP_HH
