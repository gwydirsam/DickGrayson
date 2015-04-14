#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <string>
#include "stego-crypt-lib/bmp_manip.h"

TEST(StegStub, oneEqualsone) {
  int one = 1;
  EXPECT_EQ(1, one);
}

TEST(BMPTests, BMPValidation) {
  std::ifstream ifs("test.png", std::ios::binary);
  std::string bmp;
  ifs >> bmp;
  EXPECT_EQ(true, is_bmp_valid(bmp));
}
