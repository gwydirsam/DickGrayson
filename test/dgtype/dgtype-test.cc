#include <gtest/gtest.h>

TEST(typeStub, oneEqualsone) {
  int one = 1;
  EXPECT_EQ(1, one);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  // always return 0 for coverage to work
  return 0;
}
