#include <gtest/gtest.h>

#include <iostream>
#include <dgcrypto/dgcrypto.hh>
#include <rsa-crypt-lib/rsa-crypt-lib.hh>

TEST(RSACrypt, RsaKeysConstructor17) {
  RsaKeys my_keys(16);
  EXPECT_GT(my_keys.totient(), my_keys.e());
}

TEST(RSACrypt, RsaKeysConstructor75) {
  RsaKeys my_keys(24);
  EXPECT_GT(my_keys.totient(), my_keys.e());

}

TEST(RSACrypt, RsaKeysConstructor512) {
  RsaKeys my_keys(512);
  EXPECT_GT(my_keys.totient(), my_keys.e());

}


TEST(RSACrypt, RsaKeysConstructor1024) {
  RsaKeys my_keys(1024);
  EXPECT_GT(my_keys.totient(), my_keys.e());

}
