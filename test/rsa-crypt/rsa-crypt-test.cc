#include <gtest/gtest.h>

#include <iostream>
#include <dgcrypto/dgcrypto.hh>
#include <rsa-crypt-lib/rsa-crypt-lib.hh>


TEST(RSACrypt, RsaKeysConstructor1024) {
  RsaKeys my_keys(512);
  EXPECT_GT(my_keys.totient(), my_keys.e());
}
TEST(RSACrypt, RSAEncrypt){
  RsaKeys my_keys(512);
  std::string message = "attack at dawn";
  std::string encrypted = my_keys.encrypt_message(message);
  EXPECT_NE(message, encrypted);
  EXPECT_EQ(message, my_keys.decrypt_message(encrypted));
}

TEST(RSACrypt, RSAEncryptUpperCase){
  RsaKeys my_keys(512);
  std::string message = "ATTACK AT DAWN";
  std::string encrypted = my_keys.encrypt_message(message);
  EXPECT_NE(message, encrypted);
  EXPECT_EQ(message, my_keys.decrypt_message(encrypted));
}

TEST(RSACrypt, RSAOverflowTest){
  RsaKeys my_keys(512);
  std::string message = "a";
  for(int i = 0; i < 50; ++i){
    message += "aaa";
    std::string encrypted = my_keys.encrypt_message(message);
    EXPECT_EQ(message, my_keys.decrypt_message(encrypted));
  }
}
TEST(RSACrypt, RSAEncryptMonkeyTest){
  RsaKeys my_keys(512);
  std::string message = "aaaaaaaaaaaaaaaaLONG ASS MSG FROM A MONKEYas;dlfjasd;fasdjgkasdfj 29835892069qf )@#(*%Y)aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa asdfasdf  sadfRO SALKFROO )(*&^)@#%& rolling face on keyboard asdfaskdfljasZBLAHABLHASDFfaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

  std::string encrypted = my_keys.encrypt_message(message);
  EXPECT_NE(message, encrypted);
  EXPECT_EQ(message, my_keys.decrypt_message(encrypted));
}

TEST(RSACrypt, OpenSSLVerification){
  //RsaKeys my_keys(64);
  //std::string message = "aaaaaaaaaaaaaaaaLONG ASS MSG FROM A MONKEYas;dlfjasd;fasdjgkasdfj 29835892069qf )@#(*%Y)aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa asdfasdf  sadfRO SALKFROO )(*&^)@#%& rolling face on keyboard asdfaskdfljasZBLAHABLHASDFfaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  //
  //std::string encrypted = my_keys.encrypt_message(message);
  //EXPECT_NE(message, encrypted);
  //EXPECT_EQ(message, my_keys.decrypt_message(encrypted));
  EXPECT_EQ(0,1);
}
