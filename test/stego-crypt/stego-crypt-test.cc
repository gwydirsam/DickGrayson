#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "stego-crypt-lib/bmp_manip.hh"

TEST(StegStub, oneEqualsone) {
  int one = 1;
  EXPECT_EQ(1, one);
}

TEST(BMPTests, BMPValidation) {
  std::ifstream ifs("test/stego-crypt/test.bmp");
  std::ostringstream ost;
  ost << ifs.rdbuf();
  std::string bmp(ost.str());
  EXPECT_EQ(true, is_bmp_valid(bmp));
}
