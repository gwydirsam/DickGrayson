//#include <lib/d>
//#include 
#include <gtest/gtest.h>
#include <gmpxx.h>
#include "../../lib/rsa-attack-lib/rsa-attack-lib.h"
using namespace std;

// TEST(dorothyStub, oneEqualsone) {
//   int one = 1;
//   EXPECT_EQ(1, one);
// }

TEST(factorize, smallSemiPrime) {
  mpz_class small_n = 1767_mpz;
  vector<mpz_class> expected_outputs = {31, 57};
  vector<mpz_class> actual = findFactors(small_n);
  EXPECT_EQ(expected_outputs, actual);
}

TEST(factorize, bigSemiPrime) {
  mpz_class big_n = 8884963_mpz;
  vector<mpz_class> expected_outputs = {3319_mpz, 2677_mpz};

  EXPECT_EQ(expected_outputs, findFactors(big_n));
}

TEST(factorize, smallNormalNumber) {
  mpz_class norm_num = 108;
  vector<mpz_class> expected_outputs = {2_mpz, 3_mpz, 4_mpz, 6_mpz, 9_mpz, 12_mpz, 18_mpz, 27_mpz, 36_mpz, 54_mpz};

  EXPECT_EQ(expected_outputs, findFactors(norm_num));
}
