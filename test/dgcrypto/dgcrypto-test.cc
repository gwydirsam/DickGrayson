#include <gtest/gtest.h>

#include <dgcrypto/dgcrypto.hh>

#include <sstream>

TEST(DGCryptoPrime, CreatePrimeKBits) {
  // create a prime with 16u (unsigned int 16) bits
  DG::RandomPrime sixteen(16u);
  EXPECT_GE(16u, sixteen.bits());
}

TEST(DGCryptoPrime, PrintDGPrime) {
  // create a prime with 16u (unsigned int 16) bits
  DG::RandomPrime sixteen(16u);

  StringStream stream;
  stream << sixteen;
  ""
  EXPECT_EQ(16u, sixteen.bits());
}

