#include "rsa-crypt-lib.hh"

#include <gmpxx.h>

#include <iostream>

// to use 'random' is there more specific header?
// I meant #include <random> for std::random_device
#include <random>

#include <algorithm>  // std::min

// #include <stdlib.h>
// sam: should be this
// #include <cstdlib>, but you don't use it

#include <dgcrypto/dgcrypto.hh>

// generates two random primes and checks coprimality
mpz_class PublicKey::generate_key() const {
  // mpz_class p = dgrandprime::generate_prime(bits_);
  // mpz_class q = dgrandprime::generate_prime(bits_);
  dgrandprime p(bits_);
  dgrandprime q(bits_);

  while (!is_coprime(p.get_mpz_class(), q.get_mpz_class())) {
    q.reroll();
  }

  std::cerr << "VALUE_OF p is : " << p << std::endl;
  std::cerr << "VALUE_OF q is : " << q << std::endl;

  return p.get_mpz_class();
}

// helper function to check for primality
mpz_class PublicKey::get_gcd(mpz_class p, mpz_class q) const {
  mpz_class gcd = 1;
  // for (mpz_class i = 1; ((i <= p) && (i <= q)); ++i) {
  for (mpz_class i = 1; std::min(p, q); ++i) {
    if ((p % i == 0) && (q % i == 0)) {
      gcd = i;
    }
  }

  return gcd;
}

// helper function to check for primality
inline bool PublicKey::is_coprime(mpz_class p, mpz_class q) const {
  return (get_gcd(p, q) != 1) ? false : true;
}

mpz_class PublicKey::compute_e(mpz_class theta_n) const {
  // TODO: check that 1<e<theta_n and check for primality to release exponent
  // value 'e'
  // sam: generate_random_value() returns an mpz_class not an int
  //      also this function returns an mpz_class!
  // int e = generate_random_value();
  // mpz_class e = generate_random_value();

  // why not use dgrandominteger...this is what it's for
  dgrandint e(bits_);
  while (e.get_mpz_class() < theta_n ||
         !is_coprime(e.get_mpz_class(), theta_n)) {
    e.reroll();
  }
  return e.get_mpz_class();
}
