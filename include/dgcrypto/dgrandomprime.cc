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

}
}
