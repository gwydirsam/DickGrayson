#pragma once

#include <gmpxx.h>
#include <iostream>
#include <random>

namespace DG {
namespace Crypto {
class Integer {
  // Integer is a wrapper for gmp's mpz_class
 public:
  // default constructor creates a 0
  Integer() : Integer(0_mpz) {}
  Integer(mpz_class n) : value_{n} {}

  //// accessors
  // get value
  mpz_class value() const { return value_; }
  // get value alias
  mpz_class get_mpz_class() const { return value_; }

  //// mutators
  // set value
  void value(mpz_class value) { value_ = value; }

  //// member functions
  // is value_ even
  inline bool even() const { return (value_ % 2 == 0); }

  // is value_ odd
  inline bool odd() const { return (value_ % 2 != 0); }

  //// member operators
  // postfix++
  Integer& operator++();
  // prefix++
  Integer operator++(int);
  // comparisons
  inline bool operator<(const DG::Crypto::Integer& rhs) const;
  inline bool operator>(const DG::Crypto::Integer& rhs) const;
  inline bool operator<=(const DG::Crypto::Integer& rhs) const;
  inline bool operator>=(const DG::Crypto::Integer& rhs) const;
  inline bool operator==(const DG::Crypto::Integer& rhs) const;
  inline bool operator!=(const DG::Crypto::Integer& rhs) const;
  inline bool operator<(const mpz_class& rhs) const;
  inline bool operator>(const mpz_class& rhs) const;
  inline bool operator<=(const mpz_class& rhs) const;
  inline bool operator>=(const mpz_class& rhs) const;
  inline bool operator==(const mpz_class& rhs) const;
  inline bool operator!=(const mpz_class& rhs) const;
  inline bool operator<(const int& rhs) const;
  inline bool operator>(const int& rhs) const;
  inline bool operator<=(const int& rhs) const;
  inline bool operator>=(const int& rhs) const;
  inline bool operator==(const int& rhs) const;
  inline bool operator!=(const int& rhs) const;

  //// static functions
  // is value even
  static inline bool is_even(mpz_class value) { return (value % 2 == 0); }

  // is value odd
  static inline bool is_odd(mpz_class value) { return (value % 2 != 0); }

 protected:
  //// private member variables
  // actual number
  mpz_class value_;

  //// private helper functions

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
