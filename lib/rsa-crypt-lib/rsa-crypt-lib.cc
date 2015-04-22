#include "rsa-crypt-lib.hh"

#include <gmpxx.h>

#include <iostream>
#include <tuple>      // std::tuple
#include <algorithm>  // std::min

#include <dgcrypto/dgcrypto.hh>

// to use 'random' is there more specific header?
// I meant #include <random> for std::random_device
// #include <random>
// sam: don't need this if we use dgrandprime

//always run with primes 512 bits big to make sure max value works
int NUM_BITS = 512;
mpz_class n = 0;
// generates two random primes and checks coprimality
RsaKeys::RsaKeys(mp_bitcnt_t k) : bits_{k} {
  // generate p and q
  std::tuple<mpz_class, mpz_class> keys = generate_keys();
  // compute n
  this->n_ = compute_n(std::get<0>(keys), std::get<1>(keys));
  // compute e
  this->e_ = compute_e(compute_theta_n(std::get<0>(keys), std::get<1>(keys)));
}


/*mpz_class RsaKeys::generate_public_key(int num_bits) {
  //weird I know, just for testing
  num_bits = NUM_BITS;
 
  mpz_class p = dgrprime::generate_prime(NUM_BITS); 
  mpz_class q = dgrprime::generate_prime(NUM_BITS);

  while (!is_coprime(p, q)) {
    q = dgrprime::generate_prime(NUM_BITS);
  }
  std::cout << "VALUE_OF q is : " << q << std::endl;
  n = compute_n(p,q);
  mpz_class tn = compute_theta_n(p,q);
  return p;
}*/

// helper function to check for primality
// generates two random primes and checks coprimality
const std::tuple<mpz_class, mpz_class> RsaKeys::generate_keys() const {
  // mpz_class p = dgrandprime::generate_prime(bits_);
  // mpz_class q = dgrandprime::generate_prime(bits_);
  dgrandprime p(bits_);
  dgrandprime q(bits_);

  while (!is_coprime(p.get_mpz_class(), q.get_mpz_class())) {
    q.reroll();
  }

  std::cerr << "VALUE_OF p is : " << p << std::endl;
  std::cerr << "VALUE_OF q is : " << q << std::endl;

  // return p.get_mpz_class();
  return std::make_tuple(p.get_mpz_class(), q.get_mpz_class());
}

// helper function to get gcd
const mpz_class RsaKeys::get_gcd(mpz_class p, mpz_class q) const {
  mpz_class gcd = 1;
  // for (mpz_class i = 1; ((i <= p) && (i <= q)); ++i) {
  for (mpz_class i = 1; std::min(p, q); ++i) {
    if ((p % i == 0) && (q % i == 0)) {
      gcd = i;
    }
  }

  return gcd;
}

/*mpz_class RsaKeys::generate_random_value(){
  
  mpz_class value = 0;
  // initialize random engine (can't use our member in static function)
  gmp_randclass rand_engine{gmp_randinit_default};
  
  // seed gmp_rand_alg_ with a uint from random_device
  rand_engine.seed(std::random_device{}());


  //intitialize to first non prime number so while loop executes
  value = rand_engine.get_z_bits(NUM_BITS);

  return value;
}*/

// helper function to check for primality
inline bool RsaKeys::is_coprime(mpz_class p, mpz_class q) const {
  return (get_gcd(p, q) != 1) ? false : true;
}

const mpz_class RsaKeys::compute_e(mpz_class theta_n) const {
  // TODO: check that 1<e<theta_n and check for primality to release exponent
  // value 'e'
  // sam: generate_random_value() returns an mpz_class not an int
  //      also this function returns an mpz_class!
  // int e = generate_random_value();
  // mpz_class e = generate_random_value();

  // why not use dgrandominteger...this is what it's for
  dgrandint e(bits_);
  while ((e.get_mpz_class() < theta_n) ||
         !is_coprime(e.get_mpz_class(), theta_n)) {
    e.reroll();
  }
  return e.get_mpz_class();
}
