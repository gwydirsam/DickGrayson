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
  unsigned first_pixel = bmp.get_pixel(0, 0);

  bmp.pixel_set_mask(0, 0, 0x0);
  EXPECT_EQ(first_pixel, bmp.get_pixel(0, 0));

  bmp.pixel_set_mask(0, 0, 0xFFFFFF);
  EXPECT_EQ(0xFFFFFF, bmp.get_pixel(0, 0));
}

TEST(Bmp, PixelUnsetMask) {
  dgbmp bmp("../../test/dgimg/test.bmp");
  unsigned first_pixel = bmp.get_pixel(0, 0);

  bmp.pixel_unset_mask(0, 0, 0x0);
  EXPECT_EQ(first_pixel, bmp.get_pixel(0, 0));

  bmp.pixel_unset_mask(0, 0, 0xFFFFFF);
  EXPECT_EQ(0x0, bmp.get_pixel(0, 0));
}

TEST(Bmp, MaxPixelValue) {
  dgbmp bmp("../../test/dgimg/blackrectangle.bmp");
  dgbmp bmp2("../../test/dgimg/test_24bit_max_xFFFFFF.bmp");
  EXPECT_EQ(0x0u, bmp.max_pixel_value());
  EXPECT_EQ(0xFFFFFFu, bmp2.max_pixel_value());
}
