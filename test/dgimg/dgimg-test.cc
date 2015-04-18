#include <gtest/gtest.h>
#include <fstream>
#include <dgimg/dgimg.hh>

//// helper functions which read and write BMP_data to/from file
static dgbmpdata open_bmp(const std::string& fname) {
  std::ifstream ifs(fname, std::ios::binary);
  dgbmpdata bmp;
  ifs >> bmp;
  return bmp;
}

static void write_bmp(const dgbmpdata& bmp, const std::string& fname) {
  std::ofstream ofs(fname, std::ios::binary | std::ios::trunc);
  ofs << bmp.get_byte_array();
}

TEST(BmpData, Open) {
  dgbmpdata bmp = open_bmp("test/dgimg/test.bmp");
  EXPECT_EQ(true, bmp.is_valid());
}

TEST(BmpData, IsValid) {
  dgbmpdata bmp = open_bmp("test/dgimg/test.bmp");
  EXPECT_EQ(true, bmp.is_valid());
}

TEST(BmpData, Write) {
  dgbmpdata bmp_original = open_bmp("test/dgimg/test.bmp");
  write_bmp(bmp_original, "test/dgimg/write_test.bmp");

  dgbmpdata bmp_write_test = open_bmp("test/dgimg/write_test.bmp");

  EXPECT_EQ(bmp_original.get_byte_array(), bmp_write_test.get_byte_array());
}

TEST(BmpData, BitsPerPixel) {
  dgbmpdata bmp = open_bmp("test/dgimg/test.bmp");
  EXPECT_EQ(8, bmp.bits_per_pixel());
}

TEST(BmpData, Dimensions) {
  dgbmpdata bmp = open_bmp("test/dgimg/test.bmp");
  EXPECT_EQ(512, bmp.width());
  EXPECT_EQ(512, bmp.height());
}

TEST(BmpData, PixelArraySize) {
  dgbmpdata bmp = open_bmp("test/dgimg/test.bmp");
  EXPECT_EQ(512 * 512, bmp.pixel_array_size());
}

TEST(BmpData, ImageOffset) {
  dgbmpdata bmp = open_bmp("test/dgimg/test.bmp");
  unsigned offset = bmp.image_offset();
  EXPECT_EQ(512 * 512, bmp.get_byte_array().size() - offset);
}

TEST(Bmp, ByteSetMask) {
  dgbmp bmp("test/dgimg/test.bmp");
  char first_pixel =
      bmp.get_data().get_byte_array()[bmp.get_data().image_offset()];
  bmp.byte_set_mask(0, 0x0);
  EXPECT_EQ(first_pixel,
            bmp.get_data().get_byte_array()[bmp.get_data().image_offset()]);
  bmp.byte_set_mask(0, 0xFF);
  EXPECT_EQ('\xFF',
            bmp.get_data().get_byte_array()[bmp.get_data().image_offset()]);
}

TEST(Bmp, ByteUnsetMask) {
  dgbmp bmp("test/dgimg/test.bmp");
  char first_pixel =
      bmp.get_data().get_byte_array()[bmp.get_data().image_offset()];
  bmp.byte_unset_mask(0, 0x0);
  EXPECT_EQ(first_pixel,
            bmp.get_data().get_byte_array()[bmp.get_data().image_offset()]);
  bmp.byte_unset_mask(0, 0xFF);
  EXPECT_EQ('\x00',
            bmp.get_data().get_byte_array()[bmp.get_data().image_offset()]);
}

TEST(Bmp, MaxPixelValue) {
  dgbmp bmp("test/dgimg/test_max_xFF.bmp");
  dgbmp bmp2("test/dgimg/test_black.bmp");
  dgbmp bmp3("test/dgimg/test_24bit_max_xFFFFFF.bmp");
  EXPECT_EQ(0xFF, bmp.max_pixel_value());
  EXPECT_EQ(0x0, bmp2.max_pixel_value());
  EXPECT_EQ(0xFFFFFF, bmp3.max_pixel_value());
}
