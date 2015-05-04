#include <gtest/gtest.h>

#include <iostream>
#include <dgcrypto/dgcrypto.hh>
#include <rsa-crypt-lib/rsa-crypt-lib.hh>


TEST(RSACrypt, RsaKeysConstructor1024) {
  RsaKeys my_keys(512);
  EXPECT_GT(my_keys.totient(), my_keys.e());

}

TEST(RSACrypt, RsaDecodeEncode1) {
  RsaKeys my_keys(1024);
  //std::cerr<<"Encoded value"<<my_keys.encode_result()<<std::endl;
  EXPECT_EQ("Hello my name is Rafa", my_keys.decoded_result());
}
 TEST(RSACrypt, RsaDecodeEncode2) {
  RsaKeys my_keys(1024);
  //std::cerr<<"Encoded value"<<my_keys.encode_result()<<std::endl;
  //std::cerr<<"decoded result"<<my_keys.decoded_result()<<std::endl;
  EXPECT_EQ("Hello my name is Rafa", my_keys.decoded_result());
}
