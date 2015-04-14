#ifndef BMP_MANIP_H
#define BMP_MANIP_H

#include <string>
#include <iostream>

bool is_bmp_valid(const std::string& bmp) {
  std::string validation = bmp.substr(0, 2);
  return validation == "BM";
}

#endif // BMP_MANIP_H
