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

// generates two random primes and checks coprimality
RsaKeys::RsaKeys(mp_bitcnt_t k) : bits_{k} {
  // generate p and q
  std::tuple<mpz_class, mpz_class> keys = generate_keys();
  // compute n
  this->n_ = compute_n(std::get<0>(keys), std::get<1>(keys));
  // compute totient
  this->totient_ = compute_totient(std::get<0>(keys), std::get<1>(keys));
  // compute e
  this->e_ = compute_e(this->totient_);
}

// helper function to check for primality
// generates two random primes and checks coprimality
const std::tuple<mpz_class, mpz_class> RsaKeys::generate_keys() const {
  dgrandprime p(bits_);
  dgrandprime q(bits_);

  while (!is_coprime(p.get_mpz_class(), q.get_mpz_class())) {
    q.reroll();
  }

  std::cerr << "VALUE_OF p is : " << p << std::endl;
  std::cerr << "VALUE_OF q is : " << q << std::endl;

  return std::make_tuple(p.get_mpz_class(), q.get_mpz_class());
}

// helper function to get gcd
const mpz_class RsaKeys::get_gcd(mpz_class p, mpz_class q) const {
  mpz_class gcd = 1;
  for (mpz_class i = 1; ((i <= p) && (i <= q)); ++i) {
    // for (mpz_class i = 1; i <= std::min(p, q); ++i) {
    if ((p % i == 0) && (q % i == 0)) {
      gcd = i;
    }
  }

  return gcd;
}

// helper function to check for primality
inline bool RsaKeys::is_coprime(mpz_class p, mpz_class q) const {
  return (get_gcd(p, q) != 1) ? false : true;
}

// const mpz_class RsaKeys::extended_euclidean_algorithm(mpz_class totient,
// mpz_class n) const {

// }

const mpz_class RsaKeys::compute_e(mpz_class totient) const {
  // TODO: check that 1<e<theta_n and check for primality to release exponent
  // value 'e'
  // sam: generate_random_value() returns an mpz_class not an int
  //      also this function returns an mpz_class!
  // int e = generate_random_value();
  // mpz_class e = generate_random_value();

  // why not use dgrandominteger...this is what it's for
  dgrandint e(bits_);
  while ((e.get_mpz_class() < totient) ||
         !is_coprime(e.get_mpz_class(), totient)) {
    e.reroll();
  }
  return e.get_mpz_class();
}
