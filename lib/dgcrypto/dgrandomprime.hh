#pragma once

#include <gmpxx.h>

#include <cassert>
#include <random>

#include "dgrandominteger.hh"

namespace DG {
namespace Crypto {
class RandomPrime : public RandomInteger {
  // RandomPrime is a RandomInteger that
  // makes sure it is prime *AND* can *only* be prime
 public:
  // disable default constructor
  RandomPrime() = delete;
  RandomPrime(mp_bitcnt_t k) : RandomInteger{k} {
    // the first prime number is 10b (2 in decimal), which means k must be geq 2
    assert(bits_ >= 2);
    // set value
    value_ = generate_prime(k);
  }

  // is value prime?
  // static for external use
  static bool is_prime(mpz_class value);
  static bool is_coprime(mpz_class value1, mpz_class value2);

 protected:
  // is value prime
  bool prime() { return is_prime(value_); }

  // helper for is_prime
  static mpz_class mulmod(mpz_class a, mpz_class b, mpz_class mod);

  // helper for is_prime
  static mpz_class modulo(mpz_class base, mpz_class exponent, mpz_class mod);

  // set value_ to prime of ~k bits
  mpz_class generate_prime(mp_bitcnt_t k);

  //// friend non-member functions
  // stream extraction
  friend std::ostream& operator<<(std::ostream& os,
                                  const RandomPrime& random_prime);
  // stream insertion
  friend std::istream& operator>>(std::istream& is, RandomPrime& random_prime);
};
}
}

//// aliases
// namespace alias
namespace dgcrypto = DG::Crypto;
// type alias
using dgrprime = DG::Crypto::RandomPrime;
