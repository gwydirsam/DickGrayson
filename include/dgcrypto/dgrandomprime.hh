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
  // create random prime with ~k bits, use default random algorithm (marsenne
  // twister)
  RandomPrime(mp_bitcnt_t k)
      : bits_{k}, value_{0}, gmp_rand_alg_{gmp_randinit_default} {
    // the first prime number is 10b (2 in decimal), which means k must be geq 2
    assert(bits_ >= 2);
    // seed gmp_rand_alg_ with a uint from random_device
    gmp_rand_alg_.seed(std::random_device{}());
    // set value
    value_ = generate_prime(k);
  }

  // get number of bits
  unsigned int bits() const { return bits_; }
  // get value
  mpz_class value() const { return value_; }

  // is value prime?
  // static for external use
  static bool is_prime(mpz_class value);

 private:
  //// private member variables
  // number of bits (mp_bitcnt_t is an unsigned long int)
  mp_bitcnt_t bits_;
  // actual number
  mpz_class value_;
  // GNU MP random algorithm
  gmp_randclass gmp_rand_alg_;

  //// private helper functions
  // set number of bits
  void bits(mp_bitcnt_t bits) { bits_ = bits; }
  // set value
  void value(mpz_class value) { value_ = value; }

  // is value prime
  bool prime() { return is_prime(value_); }

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
