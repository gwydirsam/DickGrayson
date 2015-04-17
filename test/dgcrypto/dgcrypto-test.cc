#include <gtest/gtest.h>

#include <gmpxx.h>
#include <stdlib.h>
#include <dgcrypto/dgcrypto.hh>

TEST(DGCryptoPrime, Prime2b) {
  // create a prime with 8 bits
  dgrprime two(2);

  EXPECT_EQ(2u, two.bits());
  
}

TEST(DGCryptoPrime, Prime4b) {
  // create a prime with 8 bits
  dgrprime four(4);

  EXPECT_EQ(4u, four.bits());
}

TEST(DGCryptoPrime, Prime8b) {
  // create a prime with 8 bits
  dgrprime eight(8);

  EXPECT_EQ(8u, eight.bits());
}

TEST(DGCryptoPrime, Prime16b) {
  EXPECT_TRUE(dgrprime::is_prime(15484517_mpz));
  // create a prime with 2 bits
  dgrprime sixteen(16);

  EXPECT_EQ(16u, sixteen.bits());

  EXPECT_GT(65535, dgrprime::is_prime(sixteen.value()));
}

TEST(DGCryptoPrime, isPrime2) {
  // create a prime with 2 bits
  dgrprime tree(3);

  EXPECT_EQ(3, tree.value());

TEST(DGCryptoPrime, isPrime3) {
  EXPECT_TRUE(dgrprime::is_prime(3_mpz));
}

TEST(DGCryptoPrime, isPrime11) {
  EXPECT_TRUE(dgrprime::is_prime(11_mpz));
}

TEST(DGCryptoPrime, isPrime59) {
  EXPECT_TRUE(dgrprime::is_prime(59_mpz));
}

TEST(DGCryptoPrime, isPrime15484517) {
  EXPECT_TRUE(dgrprime::is_prime(15484517_mpz));
}

