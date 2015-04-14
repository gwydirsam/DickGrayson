#include "dgrandomprime.hh"

#include <iostream>

namespace DG {
namespace Crypto {

// is value prime
bool RandomPrime::is_prime(mpz_class value) { return false; }

// is value_ prime
bool RandomPrime::prime() { return false; }

// set value_ to prime of ~k bits
mpz_class RandomPrime::generate_prime(unsigned int k) { return 0_mpz; }

// operators
inline bool operator<(const DG::Crypto::RandomPrime& lhs,
                      const DG::Crypto::RandomPrime& rhs) {
  return lhs.value() < rhs.value();
}
inline bool operator>(const DG::Crypto::RandomPrime& lhs,
                      const DG::Crypto::RandomPrime& rhs) {
  return rhs.value() < lhs.value();
}
inline bool operator<=(const DG::Crypto::RandomPrime& lhs,
                       const DG::Crypto::RandomPrime& rhs) {
  return !(lhs.value() > rhs.value());
}
inline bool operator>=(const DG::Crypto::RandomPrime& lhs,
                       const DG::Crypto::RandomPrime& rhs) {
  return !(lhs.value() < rhs.value());
}
inline bool operator==(const DG::Crypto::RandomPrime& lhs,
                       const DG::Crypto::RandomPrime& rhs) {
  return ((lhs.value() == lhs.value()) && (lhs.bits() == rhs.bits()));
}
inline bool operator!=(const DG::Crypto::RandomPrime& lhs,
                       const DG::Crypto::RandomPrime& rhs) {
  return !(lhs == rhs);
}

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
