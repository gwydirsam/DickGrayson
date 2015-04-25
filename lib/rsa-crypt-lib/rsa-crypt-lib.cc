#include "rsa-crypt-lib.hh"

#include <gmpxx.h>

#include <vector>

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
  mpz_class q = std::get<0>(keys);
  mpz_class p = std::get<1>(keys);
  std::cerr<<"VALUE_OF p is : "<<q<<std::endl;
  std::cerr<<"VALUE_OF q is : "<<p<<std::endl;
  // compute n
  this->n_ = compute_n(p, q);
  std::cerr<<"VALUE_OF n is : " << n() << std::endl;
  // compute totient
  this->totient_ = compute_totient(p,q);
  std::cerr<<"VALUE_OF totient is : " << totient() << std::endl; 
  // compute e
  this->e_ = compute_e(this->totient_);
  std::cerr<<"VALUE_OF e is : " << e() << std::endl;
  //compute d
 // this ->d_ = compute_d(this->totient, this->e);
  //std::cerr<<"VALUE_OF d is : " << d() << std::endl;
}

// helper function to check for primality
// generates two random primes and checks coprimality
const std::tuple<mpz_class, mpz_class> RsaKeys::generate_keys() const {
  dgrandprime p(bits_);
  dgrandprime q(bits_);
  
  //p and q don't need to be coprime
  /*while (!is_coprime(p.get_mpz_class(), q.get_mpz_class())) {
    q.reroll();
  }*/

  //std::cerr << "VALUE_OF p is : " << p << std::endl;
  //std::cerr << "VALUE_OF q is : " << q << std::endl;

  return std::make_tuple(p.get_mpz_class(), q.get_mpz_class());
}
mpz_class RsaKeys::calculate_d(mpz_class totient, mpz_class e) {
  // we want the second value: y
  mpz_class d = extended_euclidean(totient, e)[1];
  // make sure d is in our bounds

  mpz_class bounded_d = d % totient;
  // -- Function: void mpz_mod (mpz_t R, const mpz_t N, const mpz_t D)

  // C++ mod arithmetic not suitable if d is negative
  // http://stackoverflow.com/a/12089637
  if (bounded_d < 0) {
    bounded_d = bounded_d + totient;
  }

  return bounded_d;
}
std::vector<mpz_class> RsaKeys::extended_euclidean(mpz_class a, mpz_class b) {
  std::vector<mpz_class> x_y_gcd(3);

  mpz_class x, last_x, y, last_y, r, last_r;
  x = last_y = 0;
  y = last_x = 1;
  r = b;
  last_r = a;
  while (r != 0) {
    mpz_class q = last_r / r;  // floor division because of int type
    // mpz_class r = b % a;
    mpz_class tmp = r;
    r = last_r - q * tmp;
    last_r = tmp;

    tmp = x;
    x = last_x - q * tmp;
    last_x = tmp;

    tmp = y;
    y = last_y - q * tmp;
    last_y = tmp;
  }
  x_y_gcd = {last_x, last_y, last_r};
  return x_y_gcd;
}
// helper function to get gcd
const mpz_class RsaKeys::get_gcd(mpz_class p, mpz_class q) const {
  mpz_class gcd = 1;
  for (mpz_class i = 1; ((i <= p) && (i <= q)); ++i) {
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
     std::cerr<<e.get_mpz_class()<< " is not coprime with "<<totient<<std::endl;
    e.reroll();
  }
  return e.get_mpz_class();
}
