#include <gtest/gtest.h>
#include <rsa-crypt-lib/rsa-crypt-lib.hh>
#include <cstdlib.h>
TEST(CryptStub, oneEqualsone) {
  int one = 1;
  RsaKeys::RsaKeys publickey = new RsaKeys(512);
  
  EXPECT_EQ(1, one);
}


