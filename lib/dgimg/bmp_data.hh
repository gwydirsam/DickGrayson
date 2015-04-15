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

  const std::string& get_data() { return data; }
private:
  std::string data;
  int bytes_to_int(const std::string& bytes) const;
};
}
}

using dgbmpdata = DG::Image::BMP_data;

#endif // BMP_DATA_HH
