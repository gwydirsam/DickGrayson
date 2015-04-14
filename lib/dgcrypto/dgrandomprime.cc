#include "dgrandomprime.hh"

#include <iostream>

namespace DG {
namespace Crypto {

// is value prime
bool RandomPrime::is_prime(mpz_class value) { return false; }

// set value_ to prime of ~k bits
mpz_class RandomPrime::generate_prime(mp_bitcnt_t k) {
  this->value_ = gmp_rand_alg_.get_z_bits(k);
  return this->value_;
}

//// friend non-member operators
std::ostream& operator<<(std::ostream& os,
                         const DG::Crypto::RandomPrime& random_prime) {
  os << random_prime.value_;
  return os;
}

std::istream& operator>>(std::istream& is,
                         DG::Crypto::RandomPrime& random_prime) {
  // read in bits followed by value
  is >> random_prime.bits_ >> random_prime.value_;

  // figure out how to decide if this construction is invalid
  // if () is.setstate(std::ios::failbit);
  return is;
}
}
}
