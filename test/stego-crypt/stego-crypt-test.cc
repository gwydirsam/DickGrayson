#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stego-crypt-lib/stego-crypt-lib.hh>

TEST(StegStub, oneEqualsone) {
  int one = 1;
  EXPECT_EQ(1, one);
}

TEST(BmpTests, BmpValidation) {
  std::ifstream ifs("test/stego-crypt/test.bmp", std::ios::binary);
  std::ostringstream ost;
  ost << ifs.rdbuf();
  std::string bmp(ost.str());
  EXPECT_EQ(true, is_bmp_valid(bmp));
}
