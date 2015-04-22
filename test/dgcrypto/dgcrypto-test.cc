#include <gtest/gtest.h>

#include <gmpxx.h>
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
  // create a prime with 2 bits
  dgrprime sixteen(16);

  EXPECT_EQ(16u, sixteen.bits());
}

TEST(DGCryptoPrime, Prime199b) {
  // create a prime with 100 bits
  dgrprime hundred(199);

  EXPECT_EQ(199u, hundred.bits());
}

TEST(DGCryptoPrime, isPrime2) { EXPECT_TRUE(dgrprime::is_prime(2_mpz)); }
TEST(DGCryptoPrime, isPrime3) { EXPECT_TRUE(dgrprime::is_prime(3_mpz)); }
TEST(DGCryptoPrime, isPrime11) { EXPECT_TRUE(dgrprime::is_prime(11_mpz)); }
TEST(DGCryptoPrime, isPrime59) { EXPECT_TRUE(dgrprime::is_prime(59_mpz)); }
TEST(DGCryptoPrime, isPrime15484517) {
  EXPECT_TRUE(dgrprime::is_prime(15484517_mpz));
}
TEST(DGCryptoPrime, isPrimeHuge) {
  EXPECT_TRUE(dgrprime::is_prime(
      643808006803554439230129854961492699151386107534013432918073439524138264842370630061369715394739134090922937332590384720397133335969549256322620979036686633213903952966175107096769180017646161851573147596390153_mpz));
}
