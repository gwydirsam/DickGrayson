#include <gtest/gtest.h>

#include <iostream>
#include <dgcrypto/dgcrypto.hh>
#include <rsa-crypt-lib/rsa-crypt-lib.hh>

TEST(RSACrypt, RsaKeysConstructor) {
  RsaKeys my_keys(17);
  EXPECT_GT(my_keys.e(), my_keys.totient());
}

