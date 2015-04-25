#include <gtest/gtest.h>

#include <iostream>
#include <dgcrypto/dgcrypto.hh>
#include <rsa-crypt-lib/rsa-crypt-lib.hh>

// TEST(RSACrypt, RsaKeysConstructor) {
//   RsaKeys my_keys(8);

//   EXPECT_EQ(my_keys.e(), my_keys.totient());

// }

TEST(RSACryptStub, oneEqualsOne) {
  int one = 1;
  EXPECT_EQ(1, one);
}
