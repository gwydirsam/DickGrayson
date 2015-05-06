#include <gtest/gtest.h>

#include <gmpxx.h>
#include <vector>
#include <string>

#include <rsa-crypt-lib/rsa-crypt-lib.hh>
#include <rsa-attack-lib/rsa-attack-lib.hh>
#include <rsa-attack-lib/low_exponent.hh>

using namespace std;

TEST(factorize, smallSemiPrime) {
  mpz_class small_n = 48443;
  pair<mpz_class, mpz_class> expected_outputs = make_pair(193, 251);
  EXPECT_EQ(expected_outputs, rsatk::find_prime_factors(small_n));
}

TEST(factorize, bigSemiPrime) {
  mpz_class big_n = 8884963;
  pair<mpz_class, mpz_class> expected_outputs = make_pair(2677, 3319);

  // output won't be the same
  EXPECT_EQ(expected_outputs, rsatk::find_prime_factors(big_n));
}

TEST(factorize, smallNormalNumber) {
  mpz_class norm_num = 108;
  // factors are (2, 54) , (4, 27) , (9, 12) , (3, 36) , (6, 18)
  // since none of these are prime, result should be empty
  pair<mpz_class, mpz_class> expected_outputs = make_pair(0, 0);
  EXPECT_EQ(expected_outputs, rsatk::find_prime_factors(norm_num));
}

TEST(factorize, largerN) {
  mpz_class big_n = 239774199806447;

  pair<mpz_class, mpz_class> expected_outputs = make_pair(15484627, 15484661);

  // output won't be the same
  EXPECT_EQ(expected_outputs, rsatk::find_prime_factors(big_n));
  }

// test based from example in
// http://en.wikipedia.org/wiki/Extended_Euclidean_algorithm
TEST(ExtendedEuclidean, wikipediaExample) {
  mpz_class a = 240;
  mpz_class b = 46;

  mpz_class expected_x = -9;
  mpz_class expected_y = 47;
  mpz_class expected_gcd = 2;

  vector<mpz_class> actual = rsatk::extended_euclidean(a, b);
  EXPECT_EQ(expected_x, actual[0]);
  EXPECT_EQ(expected_y, actual[1]);
  EXPECT_EQ(expected_gcd, actual[2]);
}

// both of the ...CrackingRSATest fixtures pulled from here:
// http://doctrina.org/How-RSA-Works-With-Examples.html
class EasyCrackingRSATest : public ::testing::Test {
 protected:
  virtual void SetUp() { n = p * q; }

  mpz_class p = 11;  // we get this from factorization
  mpz_class q = 13;
  mpz_class e = 7;  // given(supposedly) in public key
  string m = "9";
  mpz_class n;
};

TEST_F(EasyCrackingRSATest, calculateTotient) {
  mpz_class expected_totient = 120;
  mpz_class actual_totient = rsatk::calculate_totient(p, q);
  EXPECT_EQ(expected_totient, actual_totient);
}

TEST_F(EasyCrackingRSATest, calculateD) {
  mpz_class expected_d = 103;
  mpz_class totient = rsatk::calculate_totient(p, q);
  ASSERT_EQ(120, totient);
  mpz_class actual_d = rsatk::calculate_d(totient, e);
  EXPECT_EQ(expected_d, actual_d);
}


class HarderCrackingRSATest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    // the reason for this nonstandard initialization is discussed
    // http://stackoverflow.com/a/9844465
    n = p * q;
  }
  mpz_class p =
      12131072439211271897323671531612440428472427633701410925634549312301964373042085619324197365322416866541017057361365214171711713797974299334871062829803541_mpz;
  mpz_class q =
      12027524255478748885956220793734512128733387803682075433653899983955179850988797899869146900809131611153346817050832096022160146366346391812470987105415233_mpz;
  mpz_class e = 65537;
  string m = "attack at dawn";
  mpz_class n;
};

TEST_F(HarderCrackingRSATest, calculateTotient) {
  mpz_class expected_totient =
      145906768007583323230186939349070635292401872375357164399581871019873438799005358938369571402670149802121818086292467422828157022922076746906543401224889648313811232279966317301397777852365301547848273478871297222058587457152891606459269718119268971163555070802643999529549644116811947516513938184296683521280_mpz;
  mpz_class actual_totient = rsatk::calculate_totient(p, q);
  EXPECT_EQ(expected_totient, actual_totient);
}

TEST_F(HarderCrackingRSATest, calculateD) {
  mpz_class expected_d =
      89489425009274444368228545921773093919669586065884257445497854456487674839629818390934941973262879616797970608917283679875499331574161113854088813275488110588247193077582527278437906504015680623423550067240042466665654232383502922215493623289472138866445818789127946123407807725702626644091036502372545139713_mpz;
  mpz_class totient = rsatk::calculate_totient(p, q);
  mpz_class actual_d = rsatk::calculate_d(totient, e);
  EXPECT_EQ(expected_d, actual_d);
}

TEST_F(HarderCrackingRSATest, applyPrivateKey) {
  //string encrypted_message = encrypt_message(p, q, "attack at dawn");
  string encrypted_message = RsaKeys::encrypt_message("attack at dawn", mpz_get_ui(e.get_mpz_t()), n);

  mpz_class totient = rsatk::calculate_totient(p, q);
  mpz_class d = rsatk::calculate_d(totient, e);

  string decrypted_message = RsaKeys::decrypt_message(encrypted_message, d, n);

  EXPECT_EQ(m, decrypted_message);
}

class LowExpAttacks : public ::testing::Test {
protected:
  virtual void SetUp() {
    mpz_powm(c_1.get_mpz_t(), m.get_mpz_t(), e.get_mpz_t(), n_1.get_mpz_t());
    mpz_powm(c_2.get_mpz_t(), m.get_mpz_t(), e.get_mpz_t(), n_2.get_mpz_t());
    mpz_powm(c_3.get_mpz_t(), m.get_mpz_t(), e.get_mpz_t(), n_3.get_mpz_t());

    r_1.C = mpz_get_str(NULL, 10, c_1.get_mpz_t());
    r_2.C = mpz_get_str(NULL, 10, c_2.get_mpz_t());
    r_3.C = mpz_get_str(NULL, 10, c_3.get_mpz_t());

    r_1.n = n_1;
    r_2.n = n_2;
    r_3.n = n_3;

    r_1.e = e;
    r_2.e = e;
    r_3.e = e;
  }
  rsatk::RSA_data r_1;
  rsatk::RSA_data r_2;
  rsatk::RSA_data r_3;

  mpz_class e = 3;
  mpz_class m = 102;

  mpz_class n_1 = 377;
  mpz_class n_2 = 391;
  mpz_class n_3 = 589;

  mpz_class c_1;
  mpz_class c_2;
  mpz_class c_3;
};

TEST_F(LowExpAttacks, decryption){
  mpz_class decrypted = lowexp::low_exponent_attack(r_1, r_2, r_3);
  EXPECT_EQ(m, decrypted);
}

/*
TEST(CreateTests, comod){
std::cout << "First message: " << RsaKeys::encrypt_message("Company wide message. We will attack our Rivals at dawn!", 65539,  8884963_mpz) << std::endl;
std::cout << "Second message: " << RsaKeys::encrypt_message("Company wide message. We will attack our Rivals at dawn!", 65537, 8884963_mpz) << std::endl;
}

TEST_F(EasyCrackingRSATest, applyPrivateKey) {
  string encrypted_message = RsaKeys::encrypt_message(m, mpz_get_ui(e.get_mpz_t()), n);

  mpz_class totient = rsatk::calculate_totient(p, q);
  ASSERT_EQ(120, totient);
  mpz_class d = rsatk::calculate_d(totient, e);
  ASSERT_EQ(103, d);

  string decrypted_message = RsaKeys::decrypt_message(encrypted_message, d, n);

  EXPECT_EQ(m, decrypted_message);
}
*/

