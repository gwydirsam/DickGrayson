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
    value_ = generate_prime(bits_);
  }

  // is value prime?
  // static for external use
  static bool is_prime(mpz_class value);

  // is value coprime?
  // static for external use
  // coprime := two integers a and b are said to be relatively prime, mutually
  //            prime, or coprime (also spelled co-prime) if the only
  //            positive integer that evenly divides both of them is 1. That is,
  //            the only common positive factor of the two numbers is 1
  //            - Wikipedia
  static bool is_coprime(mpz_class value1, mpz_class value2);

  // generate a random prime of ~k bits
  static mpz_class generate_prime(mp_bitcnt_t k);

 protected:
  // is value prime
  bool prime() { return is_prime(value_); }

  // helper for is_prime
  static mpz_class mulmod(mpz_class a, mpz_class b, mpz_class mod);

  // helper for is_prime
  static mpz_class modulo(mpz_class base, mpz_class exponent, mpz_class mod);

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
