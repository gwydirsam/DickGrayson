#include "dginteger.hh"

#include <iostream>
#include <cassert>
#include <random>

namespace DG {
namespace Crypto {

//// friend non-member operators
std::ostream& operator<<(std::ostream& os, const DG::Crypto::Integer& integer) {
  os << integer.value_;
  return os;
}

std::istream& operator>>(std::istream& is, DG::Crypto::Integer& integer) {
  // read in bits followed by value
  is >> integer.value_;

  // figure out how to decide if this construction is invalid
  // if () is.setstate(std::ios::failbit);
  return is;
}

//// non-member operators
inline bool operator<(const DG::Crypto::Integer& lhs,
                      const DG::Crypto::Integer& rhs) {
  return (lhs.value() < rhs.value());
}
inline bool operator>(const DG::Crypto::Integer& lhs,
                      const DG::Crypto::Integer& rhs) {
  return (rhs.value() < lhs.value());
}
inline bool operator<=(const DG::Crypto::Integer& lhs,
                       const DG::Crypto::Integer& rhs) {
  return !(lhs.value() > rhs.value());
}
inline bool operator>=(const DG::Crypto::Integer& lhs,
                       const DG::Crypto::Integer& rhs) {
  return !(lhs.value() < rhs.value());
}
inline bool operator==(const DG::Crypto::Integer& lhs,
                       const DG::Crypto::Integer& rhs) {
  return (lhs.value() == rhs.value());
}
inline bool operator!=(const DG::Crypto::Integer& lhs,
                       const DG::Crypto::Integer& rhs) {
  return !(lhs == rhs);
}
}
}
