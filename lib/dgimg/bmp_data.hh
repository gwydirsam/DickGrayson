#ifndef BMP_DATA_HH
#define BMP_DATA_HH

#include <cstdint>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>


namespace DG {
namespace Image {
struct BMP_data {
  BMP_data(const std::string& fname) { open(fname); }

  void open(const std::string& fname);
  void write(const std::string& fname);

  unsigned image_offset() const;
  unsigned bits_per_pixel() const;

  int width() const;
  int height() const;

  unsigned num_color_planes() const; // must be 1
  bool is_valid() const;

  // masks a byte of data with the specified mask
  // setting bits to 1 if they are not already 1
  // eg masking 11110000 with 00001111 sets the byte to 1111111
  void mask_set_byte(int index, unsigned mask);

  // masks a byte of data with the specified mask
  // setting bits to 0 if they are not already 0
  // eg masking 11111111 with 00001111 sets the byte to 11110000
  void mask_unset_byte(int index, unsigned mask);

  const std::string& get_data() { return data; }
private:
  std::string data;
  int bytes_to_int(const std::string& bytes) const;
};
}
}

using dgbmpdata = DG::Image::BMP_data;

#endif // BMP_DATA_HH
