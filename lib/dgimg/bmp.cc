#include <iostream>
#include "bmp.hh"

namespace DG {
namespace Image {

//// friend non-member operators
std::ostream& operator<<(std::ostream& os, const DG::Image::BMP& bmp) {
  return os;
}

std::istream& operator>>(std::istream& is, DG::Image::BMP& bmp) {
  /*
   is >> bmp.data.BM
      >> bmp.data.file_size
      >> bmp.data.reserved
      >> bmp.data.pixel_array_offset
      >> bmp.data.header_size
      >> bmp.data.width
      >> bmp.data.height
      >> bmp.data.num_color_planes
      >> bmp.data.bits_per_pixel
      >> bmp.data.compression_method
      >> bmp.data.raw_image_size
      >> bmp.data.horizontal_res
      >> bmp.data.vertical_res
      >> bmp.data.num_colors_in_palette
      >> bmp.data.num_important_colors;
  is.seekg(bmp.data.pixel_array_offset);
  uint8_t byte;
  for (int i = 0; i < bmp.data.raw_image_size; ++i) {
    is >> byte;
    tmp.data.pixel_array.push_back(byte);
  }
  */
  return is;
}

}
}
