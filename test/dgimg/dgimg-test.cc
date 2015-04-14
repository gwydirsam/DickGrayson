#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <dgimg/dgimg.hh>

static std::string bmp_file = "test/dgimg/test.bmp";

TEST(imageStub, oneEqualsone) {
  int one = 1;
  EXPECT_EQ(1, one);
}

TEST(BmpTests, Validation) {
  std::ifstream ifs(bmp_file);
  std::ostringstream ost;
  ost << ifs.rdbuf();
  std::string bmp(ost.str());
  EXPECT_EQ(true, is_bmp_valid(bmp));
}

TEST(BmpTests, Open) {
  bmp_t bmp = open_bmp(bmp_file);
  EXPECT_EQ(true, is_bmp_valid(bmp));
}

TEST(BmpTests, BitsPerPixel) {
  bmp_t bmp = open_bmp(bmp_file);
  EXPECT_EQ(8, bmp_bits_per_pixel(bmp));
}

TEST(BmpTests, Dimensions) {
  bmp_t bmp = open_bmp(bmp_file);
  EXPECT_EQ(512, bmp_width(bmp));
  EXPECT_EQ(512, bmp_height(bmp));
}

TEST(BmpTests, ImageOffset) {
  bmp_t bmp = open_bmp(bmp_file);
  unsigned offset = bmp_image_offset(bmp);
  // test.bmp is 8-bit and is 512*512
  EXPECT_EQ(512*512, bmp.size() - offset);
}
