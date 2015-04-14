#include <gtest/gtest.h>

#include <dgcrypto/dgcrypto.hh>

#include <sstream>

TEST(DGCryptoPrime, CreatePrimeKBits) {
  // create a prime with 16u (unsigned int 16) bits
  dgrprime sixteen(16u);
  EXPECT_EQ(16u, sixteen.bits());
}

TEST(DGCryptoPrime, isPrime3) {
  // create a prime with 2 bits
  dgrprime tree(2u);

  EXPECT_EQ(3, tree.value());

  EXPECT_TRUE(dgrprime::is_prime(3));
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

TEST(DGCryptoPrime, generatePrime16b) {
  EXPECT_TRUE(dgrprime::is_prime(15484517_mpz));
  // create a prime with 2 bits
  dgrprime sixteen(16u);

  EXPECT_EQ(16u, sixteen.bits());

  EXPECT_GT(65'535, dgrprime::is_prime(sixteen.value()));
}


