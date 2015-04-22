#include <gtest/gtest.h>
#include <gmpxx.h>
#include <vector>
#include <string>
#include <rsa-attack-lib/rsa-attack-lib.hh>
using namespace std;

TEST(factorize, smallSemiPrime) {
  mpz_class small_n = 48443;
  vector<pair<mpz_class, mpz_class>> expected_outputs = {
      pair<mpz_class, mpz_class>(193, 251)};
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
  //(2, 54)
  //(4, 27)
  //(9, 12)
  //(3, 36)
  //(6, 18)

  //since none of these are prime, result should be empty

  EXPECT_TRUE(rsatk::findPrimeFactors(norm_num).empty());
}

TEST(factorize, largerN) {
  mpz_class big_n = 239774199806447;

  vector<pair<mpz_class, mpz_class>> expected_outputs = {
      pair<mpz_class, mpz_class>(15484627, 15484661)};

  // output won't be the same
  EXPECT_EQ(expected_outputs, rsatk::findPrimeFactors(big_n));
}

//test based from example in http://en.wikipedia.org/wiki/Extended_Euclidean_algorithm
TEST(ExtendedEuclidean, positiveNumbers){
  mpz_class a = 240;
  mpz_class b = 46;
  mpz_class expected_gcd = 2;

  mpz_class actual_gcd = extended_euclidean(a,b);
  EXPECT_EQ(expected_gcd, actual_gcd);
}

//test pulled from here: http://doctrina.org/How-RSA-Works-With-Examples.html
class CrackingRSATest : public ::testing::Test {
protected:
  virtual void SetUp() {
    n = p * q;
  }
  //tear down?

  static const int p = 11; //we get this from factorization
  static const int q = 13;
  static const int e = 7; //given(supposedly) in public key
  static const string m = "attack at dawn"; //for testing
  int n;
};


TEST_F(CrackingRSATest, calculateTotient){
  int expected_totient = 120;
  int actual_totient = rsatk::calculate_totient(p, q);
  EXPECT_EQ(expected_totient, actual_totient);
}

//TEST(CrackingRSATest, findE){
//EXPECT_EQ(0,1);
//}
TEST(CrackingRSATest, caclculateD){
  int expected_d = 103;
  int totient = rsatk::calculate_totient(p, q);
  ASSERT_EQ(120, totient);
  int actual_d = rsatk::calculate_d(totient, e);
  EXPECT_EQ(expected_d, actual_d);
}

TEST(CrackingRSATest, applyPrivateKey){
  std::string encrypted_message = "35052111338673026690212423937053328511880760811579981620642802346685810623109850235943049080973386241113784040794704193978215378499765413083646438784740952306932534945195080183861574225226218879827232453912820596886440377536082465681750074417459151485407445862511023472235560823053497791518928820272257787786";

  decrypted_message = decrypt_message(encrypted_message, n, d);

  EXPECT_EQ(m, decrypted_message);
}


// TEST(Primes, Generate){
// generateNPrimes(1000000);
//}
