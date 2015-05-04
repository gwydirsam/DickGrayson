#include <iostream>
#include <cstdint>
#include <limits>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <dgtype/dgtype.hh>
#include "bmp.hh"

namespace DG {
namespace Image {

static RGBApixel unsigned_to_rgba(unsigned uint, int bpp) {
  uint8_t r = (uint >> 16) & 0xFF;
  uint8_t g = (uint >> 8) & 0xFF;
  uint8_t b = uint & 0xFF;
  RGBApixel rgba;
  rgba.Red = bpp == 8 ? r : std::max({r, g, b});
  rgba.Green = bpp == 8 ? g : std::max({r, g, b});
  rgba.Blue = bpp == 8 ? b : std::max({r, g, b});
  return rgba;
}

// normalizes the mask so that an 8-bit mask become
// a 24-bit mask which repeats itself every 8-bits
static unsigned normalize_mask(unsigned mask, int bpp) {
  unsigned normalized_mask = mask;
  if (bpp == 8) {
    normalized_mask &= 0xFF;
    normalized_mask |= mask << 0x10;
    normalized_mask |= mask << 0x8;
  }
  return normalized_mask;
}

void BMP::open(const std::string& fname) {
  std::ifstream ifs(fname.c_str());
  if (!ifs.good()) {
    throw Type::Inaccessible_file("BMP");
  }
  if (!data.ReadFromFile(fname.c_str())) {
    throw Type::Invalid_format("BMP");
  }
}

void BMP::write(const std::string& fname) const {
  CONST_CALL_1(data, WriteToFile, fname.c_str());
}

void BMP::pixel_set_mask(int x, int y, unsigned mask) {
  unsigned pixel = get_pixel(x, y);
  unsigned normalized_mask = normalize_mask(mask, get_bpp());
  pixel |= normalized_mask;
  RGBApixel rgba = unsigned_to_rgba(pixel, get_bpp());
  rgba.Alpha = data.GetPixel(x, y).Alpha;
  data.SetPixel(x, y, rgba);
}

void BMP::pixel_unset_mask(int x, int y, unsigned mask) {
  unsigned pixel = get_pixel(x, y);
  unsigned normalized_mask = normalize_mask(mask, get_bpp());
  pixel &= ~normalized_mask;
  RGBApixel rgba = unsigned_to_rgba(pixel, get_bpp());
  rgba.Alpha = data.GetPixel(x, y).Alpha;
  data.SetPixel(x, y, rgba);
}

unsigned BMP::get_pixel(int x, int y) const {
  uint32_t ret = 0;
  RGBApixel pixel = data.GetPixel(x, y);
  ret |= (uint8_t)pixel.Red << 16;
  ret |= (uint8_t)pixel.Green << 8;
  ret |= (uint8_t)pixel.Blue; // << 0x0;
  return ret;
}

}
}
