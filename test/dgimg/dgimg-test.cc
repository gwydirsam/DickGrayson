#include <gtest/gtest.h>
#include <fstream>
#include <dgimg/dgimg.hh>

static dgbmpdata open_bmp(const std::string& fname) {
  std::ifstream ifs(fname, std::ios::binary);
  dgbmpdata bmp;
  ifs >> bmp;
  return bmp;
}

static void write_bmp(const dgbmpdata& bmp, const std::string& fname) {
  std::ofstream ofs(fname, std::ios::binary | std::ios::trunc);
  ofs << bmp.get_data();
}

TEST(BmpData, IsValid) {
  dgbmpdata bmp = open_bmp("test/dgimg/test.bmp");
  EXPECT_EQ(true, bmp.is_valid());
}

TEST(BmpData, Open) {
  dgbmpdata bmp = open_bmp("test/dgimg/test.bmp");
  EXPECT_EQ(true, bmp.is_valid());
}

TEST(BmpData, Write) {
  dgbmpdata bmp_original = open_bmp("test/dgimg/test.bmp");
  write_bmp(bmp_original, "test/dgimg/write_test.bmp");

  dgbmpdata bmp_write_test = open_bmp("test/dgimg/write_test.bmp");

  EXPECT_EQ(bmp_original.get_data(), bmp_write_test.get_data());
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

TEST(BmpData, ImageOffset) {
  dgbmpdata bmp = open_bmp("test/dgimg/test.bmp");
  unsigned offset = bmp.image_offset();
  EXPECT_EQ(512*512, bmp.get_data().size() - offset);
}

/*
TEST(BmpData, MaskSetByte) {
  std::ifstream ifs("test/dgimg/test.bmp");
  dgbmpdata bmp;
  ifs >> bmp;
  bmp.mask_set_byte(0, 0x0);
  EXPECT_EQ('B', bmp.get_data()[0]);
  bmp.mask_set_byte(0, 0xFF);
  EXPECT_EQ('\xFF', bmp.get_data()[0]);
}

TEST(BmpData, MaskUnsetByte) {
  std::ifstream ifs("test/dgimg/test.bmp");
  dgbmpdata bmp;
  ifs >> bmp;
  bmp.mask_unset_byte(0, 0x0);
  EXPECT_EQ('B', bmp.get_data()[0]);
  bmp.mask_unset_byte(0, 0xFF);
  EXPECT_EQ('\x00', bmp.get_data()[0]);;
}*/
