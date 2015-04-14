#include "dgrandominteger.hh"

#include <iostream>

namespace DG {
namespace Crypto {

// set value_ to integer of size k bits
mpz_class RandomInteger::generate_integer(mp_bitcnt_t k) {
  this->value_ = gmp_rand_alg_.get_z_bits(k);
  return this->value_;
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

  // figure out how to decide if this construction is invalid
  // if () is.setstate(std::ios::failbit);
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
  return ((lhs.value() == lhs.value()) && (lhs.bits() == rhs.bits()));
}
inline bool operator!=(const DG::Crypto::RandomInteger& lhs,
                       const DG::Crypto::RandomInteger& rhs) {
  return !(lhs == rhs);
}
}
}
