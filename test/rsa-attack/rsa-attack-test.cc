//#include <lib/d>
#include <gtest/gtest.h>
#include <gmpxx.h>
#include "../../lib/rsa-attack-lib/rsa-attack-lib.h"
using namespace std;

// TEST(dorothyStub, oneEqualsone) {
//   int one = 1;
//   EXPECT_EQ(1, one);
// }

TEST(factorize, smallSemiPrime) {
  mpz_class small_n = 1767;
  vector<mpz_class> expected_outputs = {31, 57};
  vector<mpz_class> actual = findFactors(small_n);
  EXPECT_EQ(expected_outputs, actual);
}

TEST(factorize, bigSemiPrime) {
  mpz_class big_n = 8884963;
  vector<mpz_class> expected_outputs = {3319, 2677};

  //output won't be the same
  EXPECT_EQ(expected_outputs, findFactors(big_n));
}

TEST(factorize, smallNormalNumber) {
  mpz_class norm_num = 108;
  vector<mpz_class> expected_outputs = {2, 3, 4, 6, 9, 12, 18, 27, 36, 54};

  EXPECT_EQ(expected_outputs, findFactors(norm_num));
}
