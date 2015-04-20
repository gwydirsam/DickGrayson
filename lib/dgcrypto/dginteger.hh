#pragma once

#include <gmpxx.h>

#include <iosfwd>
#include <cassert>
#include <random>

namespace DG {
namespace Crypto {
class Integer {
  // Integer is a wrapper for gmp's mpz_class
 public:
  // disable default constructor
  Integer() = delete;
  Integer(mpz_class n) : value_{n} {}

  // get value
  mpz_class value() const { return value_; }

 protected:
  //// private member variables
  // actual number
  mpz_class value_;

  //// private helper functions
  // set value
  void value(mpz_class value) { value_ = value; }

  //// friend non-member functions
  // stream extraction
  friend std::ostream& operator<<(std::ostream& os, const Integer& integer);
  // stream insertion
  friend std::istream& operator>>(std::istream& is, Integer& integer);
};
}
}

//// aliases
// namespace alias
namespace dgcrypto = DG::Crypto;
// type alias
using dgint = DG::Crypto::Integer;
