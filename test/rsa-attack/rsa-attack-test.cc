#include <gtest/gtest.h>
#include <gmpxx.h>
#include <vector>
#include <rsa-attack-lib/rsa-attack-lib.hh>
using namespace std;

TEST(factorize, smallSemiPrime) {
  mpz_class small_n = 1767;
  vector<pair<mpz_class, mpz_class>> expected_outputs = {
      pair<mpz_class, mpz_class>(31, 57)};
  EXPECT_EQ(expected_outputs, rsatk::findPrimeFactors(small_n));
}

TEST(factorize, bigSemiPrime) {
  mpz_class big_n = 8884963;
  vector<pair<mpz_class, mpz_class>> expected_outputs = {
      pair<mpz_class, mpz_class>(2677, 3319)};

  // output won't be the same
  EXPECT_EQ(expected_outputs, rsatk::findPrimeFactors(big_n));
}

TEST(factorize, smallNormalNumber) {
  mpz_class norm_num = 108;
  vector<pair<mpz_class, mpz_class>> expected_outputs = {
      pair<mpz_class, mpz_class>(2, 54), pair<mpz_class, mpz_class>(3, 36),
      pair<mpz_class, mpz_class>(4, 27), pair<mpz_class, mpz_class>(6, 18),
      pair<mpz_class, mpz_class>(9, 12)};

  EXPECT_EQ(expected_outputs, rsatk::findPrimeFactors(norm_num));
}

TEST(factorize, largerN) {
  mpz_class big_n = 239774199806447;

  vector<pair<mpz_class, mpz_class>> expected_outputs = {
      pair<mpz_class, mpz_class>(15484627, 15484661)};

  // output won't be the same
  EXPECT_EQ(expected_outputs, rsatk::findPrimeFactors(big_n));
}

TEST(itermediate, generateTotient){
   EXPECT_EQ(0,1);
 }
TEST(itermediate, findE){
  EXPECT_EQ(0,1);
}
TEST(decrypt, generateDSimple){
  EXPECT_EQ(0,1);
}
TEST(decrypt, generateDComplex){
  EXPECT_EQ(0,1);
}
TEST(decrypt, generatePrivateKey){
  EXPECT_EQ(0,1);
}
TEST(decrypt, applyPrivateKey){
  EXPECT_EQ(0,1);
}


// TEST(Primes, Generate){
// generateNPrimes(1000000);
//}
