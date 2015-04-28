#pragma once

#include <string>
#include <exception>
#include "EasyBMP.h"
#include "bmp_data.hh"

// typedef the EasyBMP BMP class to Easy_bmp
typedef BMP Easy_bmp;

// EasyBMP library doesn't declare some functions const, this allows us to use
// those functions even on const objects
#define CONST_FUNC(obj, func) const_cast<decltype(obj)*>(&obj)->func
#define CONST_CALL(obj, func) CONST_FUNC(obj, func)()
#define CONST_CALL_1(obj, func, arg) CONST_FUNC(obj, func)(arg) // pass arg to func

namespace DG {
namespace Image {

class BMP {
 public:
  BMP() {SetEasyBMPwarningsOff();}
  BMP(const std::string& fname) :BMP() { open(fname); }

  // opens a bmp file fname and stores it
  void open(const std::string& fname);

  // saves the bmp data out to the file fname
  void write(const std::string& fname) const;

  // masks a pixel with the specified mask
  // setting bits to 1 if they are not already 1
  // eg masking 11110000 with 00001111 sets the byte to 1111111
  void pixel_set_mask(int x, int y, unsigned mask);

  // masks a pixe with the specified mask
  // setting bits to 0 if they are not already 0
  // eg masking 11111111 with 00001111 sets the byte to 11110000
  void pixel_unset_mask(int x, int y, unsigned mask);

  unsigned max_pixel_value() const;
  double mean_squared_error(const BMP& other) const;
  double peak_signal_noise_ratio(const BMP& other) const;

  //// getters

  const Easy_bmp& get_data() const { return data; }
  unsigned get_pixel(int x, int y) const;

  int get_bpp() const {
    return CONST_CALL(data, TellBitDepth);
  }

  int get_width() const {
    return CONST_CALL(data, TellWidth);
  }

  int get_height() const {
    return CONST_CALL(data, TellHeight);
  }

  int get_num_pixels() const {
    return get_width() * get_height();
  }

 private:
  //BMP_data data;
  Easy_bmp data;

};

}
}

//// aliases
// namespace alias
namespace dgimg = DG::Image;
// type alias
using dgbmp = DG::Image::BMP;
