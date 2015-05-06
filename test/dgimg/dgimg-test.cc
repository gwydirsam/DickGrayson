#include <gtest/gtest.h>
#include <fstream>
#include <dgtype/dgtype.hh>
#include <dgimg/dgimg.hh>

////// BMP TESTS

TEST(Bmp, InvalidFormatException) {
  ASSERT_THROW(dgbmp png("../../test/dgimg/badformat.png"),
               dgtype::Invalid_format_exception);
}

TEST(Bmp, InaccessibleFileException) {
  ASSERT_THROW(dgbmp bmp("../../test/dgimg/imaginary.bmp"),
               dgtype::Inaccessible_file_exception);
}

TEST(Bmp, PixelSetMask) {
  dgbmp bmp("../../test/dgimg/test.bmp");
  unsigned first_pixel = bmp.get_pixel(0, 0);

  bmp.pixel_set_mask(0, 0, 0x0);
  EXPECT_EQ(first_pixel, bmp.get_pixel(0, 0));

  bmp.pixel_set_mask(0, 0, 0xFFFFFF);
  EXPECT_EQ(0xFFFFFFu, bmp.get_pixel(0, 0));
}

TEST(Bmp, PixelUnsetMask) {
  dgbmp bmp("../../test/dgimg/test.bmp");
  unsigned first_pixel = bmp.get_pixel(0, 0);

  bmp.pixel_unset_mask(0, 0, 0x0);
  EXPECT_EQ(first_pixel, bmp.get_pixel(0, 0));

  bmp.pixel_unset_mask(0, 0, 0xFFFFFF);
  EXPECT_EQ(0x0u, bmp.get_pixel(0, 0));
}
