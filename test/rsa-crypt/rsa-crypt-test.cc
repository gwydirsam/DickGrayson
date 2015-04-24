#include <gtest/gtest.h>

#include <iostream>
#include <dgcrypto/dgcrypto.hh>
#include <rsa-crypt-lib/rsa-crypt-lib.hh>

TEST(RSACrypt, RsaKeysConstructor) {
  RsaKeys my_keys(512);

  EXPECT_EQ(512ul, my_keys.bits());
}
