#include <gtest/gtest.h>
#include <fstream>
#include <dgimg/dgimg.hh>

////// BMP TESTS

TEST(Bmp, InvalidFormatException) {
  ASSERT_THROW(dgbmp png("../../test/dgimg/badformat.png"),
               dgbmp::Invalid_format_exception);
}

TEST(Bmp, PixelSetMask) {
  dgbmp bmp("../../test/dgimg/test.bmp");
  char first_pixel = bmp.get_pixel(0, 0);

  bmp.pixel_set_mask(0, 0, 0x0);
  EXPECT_EQ(first_pixel, bmp.get_pixel(0, 0));

  bmp.pixel_set_mask(0, 0, 0xFF);
  EXPECT_EQ(first_pixel, bmp.get_pixel(0, 0));
}

TEST(Bmp, PixelUnsetMask) {
  dgbmp bmp("../../test/dgimg/test.bmp");
  char first_pixel = bmp.get_pixel(0, 0);

  bmp.pixel_unset_mask(0, 0, 0x0);
  EXPECT_EQ(first_pixel, bmp.get_pixel(0, 0));

  bmp.pixel_unset_mask(0, 0, 0xFF);
  EXPECT_EQ('\x00', bmp.get_pixel(0, 0));
}

TEST(Bmp, MaxPixelValue) {
  dgbmp bmp("../../test/dgimg/blackrectangle.bmp");
  dgbmp bmp2("../../test/dgimg/test_24bit_max_xFFFFFF.bmp");
  EXPECT_EQ(0x0u, bmp.max_pixel_value());
  EXPECT_EQ(0xFFFFFFu, bmp2.max_pixel_value());
}

////// BMP_DATA TESTS

/*
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
  dgbmpdata bmp = open_bmp("../../test/dgimg/test.bmp");
  EXPECT_EQ(true, bmp.is_valid());
}

TEST(BmpData, IsValid) {
  dgbmpdata bmp = open_bmp("../../test/dgimg/test.bmp");
  EXPECT_EQ(true, bmp.is_valid());
}

TEST(BmpData, Write) {
  dgbmpdata bmp_original = open_bmp("../../test/dgimg/test.bmp");
  write_bmp(bmp_original, "../../test/dgimg/write_test.bmp");

  dgbmpdata bmp_write_test = open_bmp("../../test/dgimg/write_test.bmp");

  EXPECT_EQ(bmp_original.get_byte_array(), bmp_write_test.get_byte_array());
}

TEST(BmpData, BitsPerPixel) {
  dgbmpdata bmp = open_bmp("../../test/dgimg/test.bmp");
  EXPECT_EQ(8u, bmp.bits_per_pixel());
}

TEST(BmpData, Dimensions) {
  dgbmpdata bmp = open_bmp("../../test/dgimg/test.bmp");
  EXPECT_EQ(512, bmp.width());
  EXPECT_EQ(512, bmp.height());
}

TEST(BmpData, PixelArraySize) {
  dgbmpdata bmp = open_bmp("../../test/dgimg/test.bmp");
  EXPECT_EQ(512u * 512u, bmp.pixel_array_size());
}

TEST(BmpData, ImageOffset) {
  dgbmpdata bmp = open_bmp("../../test/dgimg/test.bmp");
  unsigned offset = bmp.image_offset();
  EXPECT_EQ(512u * 512u, bmp.get_byte_array().size() - offset);
} */
