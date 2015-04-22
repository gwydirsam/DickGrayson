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
  EXPECT_EQ(expected_outputs, rsatk::find_prime_factors(small_n));
}

TEST(factorize, bigSemiPrime) {
  mpz_class big_n = 8884963;
  vector<pair<mpz_class, mpz_class>> expected_outputs = {
      pair<mpz_class, mpz_class>(2677, 3319)};

  // output won't be the same
  EXPECT_EQ(expected_outputs, rsatk::find_prime_factors(big_n));
}

TEST(factorize, smallNormalNumber) {
  mpz_class norm_num = 108;
  //factors are (2, 54) , (4, 27) , (9, 12) , (3, 36) , (6, 18)
  //since none of these are prime, result should be empty
  EXPECT_TRUE(rsatk::find_prime_factors(norm_num).empty());
}

TEST(factorize, largerN) {
  mpz_class big_n = 239774199806447;

  vector<pair<mpz_class, mpz_class>> expected_outputs = {
      pair<mpz_class, mpz_class>(15484627, 15484661)};

  // output won't be the same
  EXPECT_EQ(expected_outputs, rsatk::find_prime_factors(big_n));
}

//test based from example in http://en.wikipedia.org/wiki/Extended_Euclidean_algorithm
TEST(ExtendedEuclidean, wikipediaExample){
  mpz_class a = 240;
  mpz_class b = 46;

  mpz_class expected_x = -9;
  mpz_class expected_y = 47;
  mpz_class expected_gcd = 2;

  vector<mpz_class> actual = rsatk::extended_euclidean(a,b);
  EXPECT_EQ(expected_x, actual[0]);
  EXPECT_EQ(expected_y, actual[1]);
  EXPECT_EQ(expected_gcd, actual[2]);
}

//test pulled from here: http://doctrina.org/How-RSA-Works-With-Examples.html
class EasyCrackingRSATest : public ::testing::Test {
protected:
  virtual void SetUp() {
    n = p * q;
  }

  mpz_class p = 11; //we get this from factorization
  mpz_class q = 13;
  mpz_class e = 7; //given(supposedly) in public key
  string m = "9";
  mpz_class n;
};


  TEST_F(EasyCrackingRSATest, calculateTotient){
    mpz_class expected_totient = 120;
    mpz_class actual_totient = rsatk::calculate_totient(p, q);
    EXPECT_EQ(expected_totient, actual_totient);
  }

  TEST_F(EasyCrackingRSATest, calculateD){
    mpz_class expected_d = 103;
    mpz_class totient = rsatk::calculate_totient(p, q);
    ASSERT_EQ(120, totient);
    mpz_class actual_d = rsatk::calculate_d(totient, e);
    EXPECT_EQ(expected_d, actual_d);
  }

  TEST_F(EasyCrackingRSATest, applyPrivateKey){
    string encrypted_message = "48";

    mpz_class totient = rsatk::calculate_totient(p, q);
    ASSERT_EQ(120, totient);
    mpz_class d = rsatk::calculate_d(totient, e);
    ASSERT_EQ(103, d);

    string decrypted_message = rsatk::decrypt_message(encrypted_message, n, d);

    EXPECT_EQ(m, decrypted_message);
  }

/*
  TEST(PublicKeyReading, findE){
  EXPECT_EQ(0,1); //dummy
}

 TEST(Primes, Generate){
 generate_n_primes(1000000);
 }
*/
