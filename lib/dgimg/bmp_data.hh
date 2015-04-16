#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>


namespace DG {
namespace Image {
struct BMP;
struct BMP_data {

  unsigned image_offset() const;
  unsigned bits_per_pixel() const;

  int width() const;
  int height() const;

  unsigned pixel_array_size() const;

  unsigned num_color_planes() const; // must be 1
  bool is_valid() const;

  const std::string& get_byte_array() const { return byte_array; }
  const std::string& get_pixel_array() const { return pixel_array; }
private:
  std::string byte_array;
  std::string pixel_array;
  int bytes_to_int(const std::string& bytes) const;

  friend std::ostream& operator<<(std::ostream& os, const BMP_data& bmp);
  friend std::istream& operator>>(std::istream& is, BMP_data& bmp);
  friend BMP;
};
}
}

using dgbmpdata = DG::Image::BMP_data;
