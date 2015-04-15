#include <iostream>
#include "bmp.hh"

namespace DG {
namespace Image {

//// friend non-member operators
std::ostream& operator<<(std::ostream& os, const DG::Image::BMP& bmp) {
  return os;
}

std::istream& operator>>(std::istream& is, DG::Image::BMP& bmp) {
  return is;
}

}
}
