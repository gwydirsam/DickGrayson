#pragma once

#include <gmpxx.h>

#include <cassert>
#include <random>

namespace DG {
namespace Crypto {

// template <typename RAND_ENGINE_T>
class RandomPrime {
 public:
  // disable default constructor
  RandomPrime() = delete;
  // create random prime with ~k bits
  RandomPrime(unsigned int k) : bits_{} {
    // assert(bits_ >= 1u);
    // value_ = generate_prime(k);
  }

  // get number of bits
  unsigned int bits() const { return bits_; }
  // get value
  mpz_class value() const { return value_; }

  // is value prime
  static bool is_prime(mpz_class value);

 private:
  // set number of bits
  void bits(unsigned int bits) { bits_ = bits; }
  // set value
  void value(mpz_class value) { value_ = value; }

  // is value prime
  bool prime();

  // set value_ to prime of ~k bits
  mpz_class generate_prime(unsigned int k);

  // stream extraction
  friend std::ostream& operator<<(std::ostream& os,
                                  const RandomPrime& random_prime);

  // stream insertion
  friend std::istream& operator>>(std::istream& is, RandomPrime& random_prime);

  // number of bits
  unsigned int bits_;
  // actual number
  mpz_class value_;
};
}
}

namespace dgcrypto = DG::Crypto;
using dgrprime = DG::Crypto::RandomPrime;

