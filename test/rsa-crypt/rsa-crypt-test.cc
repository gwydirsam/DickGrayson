#include <gtest/gtest.h>

#include <iostream>
#include <dgcrypto/dgcrypto.hh>
#include <rsa-crypt-lib/rsa-crypt-lib.hh>

TEST(rsaCryptStub, oneEqualsOne) {
  int one = 1;
  EXPECT_EQ(1, one);
}

// TEST(RSACrypt, RsaKeysConstructor) {
//   RsaKeys my_keys(1024);

//   EXPECT_EQ(1024ul, my_keys.bits());
// }
