#include <gtest/gtest.h>
#include <dgimg/dgimg.hh>


TEST(imageStub, oneEqualsone) {
  int one = 1;
  EXPECT_EQ(1, one);
}

TEST(BmpData, isValid) {
  dgbmpdata bmp("test/dgimg/test.bmp");
  EXPECT_EQ(true, bmp.is_valid());
}

TEST(BmpData, Open) {
  dgbmpdata bmp("test/dgimg/test.bmp");
  EXPECT_EQ(true, bmp.is_valid());
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
  // test.bmp is 8-bit and is 512*512
  EXPECT_EQ(512*512, bmp.get_data().size() - offset);
}
