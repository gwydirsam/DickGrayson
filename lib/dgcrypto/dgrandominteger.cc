#include "dgrandominteger.hh"

#include <gmp.h>
#include <gmpxx.h>

#include <iostream>
#include <cassert>
#include <random>

namespace DG {
namespace Crypto {

// set value_ to integer of size k bits
mpz_class RandomInteger::generate_integer(mp_bitcnt_t k) {
  this->value_ = gmp_rand_alg_.get_z_bits(k);
  return this->value_;
}

// returns the maximum number this object can hold
const mpz_class RandomInteger::max_size() const {
  // initialize max_num to 0
  mpz_class max_num(0_mpz);
  // our base is 2 for binary
  mpz_class binary_base(2_mpz);
  // set max_num to 2^(random_integer.bits_) - 1
  mpz_mul_2exp(max_num.get_mpz_t(), binary_base.get_mpz_t(), this->bits_);
  max_num -= 1;
  return max_num;
}

//// friend non-member operators
std::ostream& operator<<(std::ostream& os,
                         const DG::Crypto::RandomInteger& random_integer) {
  os << random_integer.value_;
  return os;
}

std::istream& operator>>(std::istream& is,
                         DG::Crypto::RandomInteger& random_integer) {
  // read in bits followed by value
  is >> random_integer.bits_ >> random_integer.value_;

  // if value is greater than the maximum number allowed in n bits, set failbit
  if (random_integer.value_ > random_integer.max_size()) {
    is.setstate(std::ios::failbit);
  }
  return is;
}

//// non-member operators
inline bool operator<(const DG::Crypto::RandomInteger& lhs,
                      const DG::Crypto::RandomInteger& rhs) {
  return (lhs.value() < rhs.value());
}
inline bool operator>(const DG::Crypto::RandomInteger& lhs,
                      const DG::Crypto::RandomInteger& rhs) {
  return (rhs.value() < lhs.value());
}
inline bool operator<=(const DG::Crypto::RandomInteger& lhs,
                       const DG::Crypto::RandomInteger& rhs) {
  return !(lhs.value() > rhs.value());
}
inline bool operator>=(const DG::Crypto::RandomInteger& lhs,
                       const DG::Crypto::RandomInteger& rhs) {
  return !(lhs.value() < rhs.value());
}
inline bool operator==(const DG::Crypto::RandomInteger& lhs,
                       const DG::Crypto::RandomInteger& rhs) {
  return ((lhs.value() == rhs.value()) && (lhs.bits() == rhs.bits()));
}
inline bool operator!=(const DG::Crypto::RandomInteger& lhs,
                       const DG::Crypto::RandomInteger& rhs) {
  return !(lhs == rhs);
}
}
}
