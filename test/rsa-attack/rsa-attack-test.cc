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
   vector<pair<mpz_class, mpz_class > > expected_outputs = {
     pair<mpz_class, mpz_class >(31, 57)
   };
   EXPECT_EQ(expected_outputs, findFactors(small_n));
 }

 TEST(factorize, bigSemiPrime) {
   mpz_class big_n = 8884963;
   vector<pair<mpz_class, mpz_class > > expected_outputs = {
     pair<mpz_class, mpz_class >(2677, 3319)
   };

   //output won't be the same
   EXPECT_EQ(expected_outputs, findFactors(big_n));
 }

TEST(factorize, smallNormalNumber) {
  mpz_class norm_num = 108;
  vector<pair<mpz_class, mpz_class > > expected_outputs = {
    pair<mpz_class, mpz_class >(2, 54),
    pair<mpz_class, mpz_class >(3, 36),
    pair<mpz_class, mpz_class >(4, 27),
    pair<mpz_class, mpz_class >(6, 18),
    pair<mpz_class, mpz_class >(9, 12)
  };

  EXPECT_EQ(expected_outputs, findFactors(norm_num));
}
