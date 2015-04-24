#include <gtest/gtest.h>
#include <sndfile.h>

TEST(sndStub, oneEqualsone) {
  int one = 1;
  EXPECT_EQ(1, one);
}

TEST(sndStub, libSndFileOpen) {
  int two = 2;
  EXPECT_EQ(2, two);
}
