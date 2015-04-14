#pragma once

#include <gmpxx.h>
#include <random>

// using dgrprime = RandomPrime<gmp

namespace DG {
// template <typename RAND_ENGINE_T>
class RandomPrime {
 public:
  // disable default constructor
  RandomPrime() = delete;
  // create random prime with ~k bits
  RandomPrime(unsigned int k) : bits_{k} {}

  // get number of bits
  unsigned int bits() const { return bits_; }
  // get value
  mpz_class value() const { return value_; }


  // stream extraction
  friend std::ostream& operator<<(std::ostream& os, const DG::RandomPrime& random_prime);

  // stream insertion
  friend std::istream& operator>>(std::istream& is, DG::RandomPrime& random_prime);

 private:
  // set number of bits
  void bits(unsigned int bits) { bits_ = bits; }
  // set value
  void value(mpz_class value) { value_ = value; }


  // number of bits
  unsigned int bits_;
  // actual number
  mpz_class value_;
};
}
