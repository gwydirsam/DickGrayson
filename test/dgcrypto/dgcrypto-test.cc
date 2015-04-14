#include <gtest/gtest.h>

#include <dgcrypto/dgcrypto.hh>

TEST(DGCryptoPrime, CreatePrimeKBits) {
  // create a prime with 16u (unsigned int 16) bits
  DGPrime sixteen(16u);
  EXPECT_GT(8u, sixteen.bits());
}

