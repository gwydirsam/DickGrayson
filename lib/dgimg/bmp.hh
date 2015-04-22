#pragma once

#include <string>
#include <exception>
#include "bmp_data.hh"

namespace DG {
namespace Image {
class BMP {
 public:
  struct Invalid_format_exception : public std::exception {
    virtual const char* what() const throw() {
      return "BMP: Invalid_format_exception";
    }
  } invalid_format;

  BMP() {}
  BMP(const std::string& fname) { open(fname); }
  void open(const std::string& fname);
  void write(const std::string& fname);

  // masks a byte from the byte array with the specified mask
  // setting bits to 1 if they are not already 1
  // eg masking 11110000 with 00001111 sets the byte to 1111111
  void byte_set_mask(int index, unsigned mask);

  // masks a byte from byte array with the specified mask
  // setting bits to 0 if they are not already 0
  // eg masking 11111111 with 00001111 sets the byte to 11110000
  void byte_unset_mask(int index, unsigned mask);

  unsigned max_pixel_value() const;
  double mean_squared_error(const BMP& other) const;
  double peak_signal_noise_ratio(const BMP& other) const;

  const BMP_data& get_data() const { return data; }
  unsigned get_pixel(int x, int y) const;

  int get_num_pixels() const { return data.width() * data.height(); }

 private:
  BMP_data data;

  friend std::ostream& operator<<(std::ostream& os, const BMP& bmp);
  friend std::istream& operator>>(std::istream& is, BMP& bmp);
};
}
}

//// aliases
// namespace alias
namespace dgimg = DG::Image;
// type alias
using dgbmp = DG::Image::BMP;
