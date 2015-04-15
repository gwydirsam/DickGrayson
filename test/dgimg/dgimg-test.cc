#include <gtest/gtest.h>
#include <dgimg/dgimg.hh>

TEST(BmpData, IsValid) {
  dgbmpdata bmp("test/dgimg/test.bmp");
  EXPECT_EQ(true, bmp.is_valid());
}

TEST(BmpData, Open) {
  dgbmpdata bmp("test/dgimg/test.bmp");
  EXPECT_EQ(true, bmp.is_valid());
}

TEST(BmpData, Write) {
  dgbmpdata bmp_original("test/dgimg/test.bmp");
  bmp_original.write("test/dgimg/write_test.bmp");
  dgbmpdata bmp_write_test("test/dgimg/write_test.bmp");
  EXPECT_EQ(bmp_original.get_data(), bmp_write_test.get_data());
}

TEST(BmpData, BitsPerPixel) {
  dgbmpdata bmp("test/dgimg/test.bmp");
  EXPECT_EQ(8, bmp.bits_per_pixel());
}

TEST(BmpData, Dimensions) {
  dgbmpdata bmp("test/dgimg/test.bmp");
  EXPECT_EQ(512, bmp.width());
  EXPECT_EQ(512, bmp.height());
}

TEST(BmpData, ImageOffset) {
  dgbmpdata bmp("test/dgimg/test.bmp");
  unsigned offset = bmp.image_offset();
  EXPECT_EQ(512*512, bmp.get_data().size() - offset);
}

TEST(BmpData, MaskByte) {
  dgbmpdata bmp("test/dgimg/test.bmp");
  bmp.mask_byte(0, 0x0);
  EXPECT_EQ('B', bmp.get_data()[0]);
  bmp.mask_byte(0, 0xFF);
  EXPECT_EQ('\xFF', bmp.get_data()[0]);
}
