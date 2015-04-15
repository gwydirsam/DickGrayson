#ifndef BMP_HH
#define BMP_HH

#include <string>
#include "bmp_data.hh"

namespace DG {
namespace Image {
class BMP {
public:

private:
  BMP_data data;

  friend std::ostream& operator<<(std::ostream& os, const BMP& bmp);
  friend std::istream& operator>>(std::istream& is, BMP& bmp);
};
}
}


#endif // BMP_HH

//// aliases
// namespace alias
namespace dgimg = DG::Image;
// type alias
using dgbmp = DG::Image::BMP;
