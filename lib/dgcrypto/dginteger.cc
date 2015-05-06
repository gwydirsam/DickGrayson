#include "dginteger.hh"

#include <gmpxx.h>
#include <iostream>
#include <cassert>
#include <random>

namespace DG {
namespace Crypto {

mpz_class mod(mpz_class num, mpz_class modulo){
  // -- Function: void mpz_mod (mpz_t R, const mpz_t N, const mpz_t D)

  // C++ mod arithmetic not suitable if d is negative
  // http://stackoverflow.com/a/12089637
  mpz_class bounded = num % modulo;

  if(bounded < 0) {
    bounded = bounded + modulo;
  }

  return bounded;
}

//// member operators
// postfix++
Integer& Integer::operator++() {
  value_++;
  return *this;
}

// prefix++
Integer Integer::operator++(int) {
  DG::Crypto::Integer tmp(*this);  // copy
  operator++();                    // pre-increment
  return tmp;                      // return old value
}

inline bool Integer::operator<(const DG::Crypto::Integer& rhs) const {
  return (this->value() < rhs.value());
}
inline bool Integer::operator>(const DG::Crypto::Integer& rhs) const {
  return (rhs.value() < this->value());
}
inline bool Integer::operator<=(const DG::Crypto::Integer& rhs) const {
  return !(this->value() > rhs.value());
}
inline bool Integer::operator>=(const DG::Crypto::Integer& rhs) const {
  return !(this->value() < rhs.value());
}
inline bool Integer::operator==(const DG::Crypto::Integer& rhs) const {
  return (this->value() == rhs.value());
}
inline bool Integer::operator!=(const DG::Crypto::Integer& rhs) const {
  return !(*this == rhs);
}

inline bool Integer::operator<(const mpz_class& rhs) const {
  return (this->get_mpz_class() < rhs);
}
inline bool Integer::operator>(const mpz_class& rhs) const {
  return (this->get_mpz_class() > rhs);
}
inline bool Integer::operator<=(const mpz_class& rhs) const {
  return !(*this > rhs);
}
inline bool Integer::operator>=(const mpz_class& rhs) const {
  return !(*this < rhs);
}
inline bool Integer::operator==(const mpz_class& rhs) const {
  return (this->get_mpz_class() == rhs);
}
inline bool Integer::operator!=(const mpz_class& rhs) const {
  return !(*this == rhs);
}

inline bool Integer::operator<(const int& rhs) const {
  return (this->get_mpz_class().get_si() < rhs);
}
inline bool Integer::operator>(const int& rhs) const {
  return (this->get_mpz_class().get_si() > rhs);
}
inline bool Integer::operator<=(const int& rhs) const { return !(*this > rhs); }
inline bool Integer::operator>=(const int& rhs) const { return !(*this < rhs); }
inline bool Integer::operator==(const int& rhs) const {
  return (this->get_mpz_class().get_si() == rhs);
}
inline bool Integer::operator!=(const int& rhs) const {
  return !(*this == rhs);
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
  return !(lhs.value() == rhs.value());
}

inline bool operator<(const DG::Crypto::Integer& lhs, const mpz_class& rhs) {
  return (lhs.value() < rhs);
}
inline bool operator>(const DG::Crypto::Integer& lhs, const mpz_class& rhs) {
  return (rhs < lhs.value());
}
inline bool operator<=(const DG::Crypto::Integer& lhs, const mpz_class& rhs) {
  return !(lhs.value() > rhs);
}
inline bool operator>=(const DG::Crypto::Integer& lhs, const mpz_class& rhs) {
  return !(lhs.value() < rhs);
}
inline bool operator==(const DG::Crypto::Integer& lhs, const mpz_class& rhs) {
  return (lhs.value() == rhs);
}
inline bool operator!=(const DG::Crypto::Integer& lhs, const mpz_class& rhs) {
  return !(lhs.value() == rhs);
}

inline bool operator<(const DG::Crypto::Integer& lhs, const int& rhs) {
  return (lhs.value() < rhs);
}
inline bool operator>(const DG::Crypto::Integer& lhs, const int& rhs) {
  return (rhs < lhs.value());
}
inline bool operator<=(const DG::Crypto::Integer& lhs, const int& rhs) {
  return !(lhs.value() > rhs);
}
inline bool operator>=(const DG::Crypto::Integer& lhs, const int& rhs) {
  return !(lhs.value() < rhs);
}
inline bool operator==(const DG::Crypto::Integer& lhs, const int& rhs) {
  return (lhs.value() == rhs);
}
inline bool operator!=(const DG::Crypto::Integer& lhs, const int& rhs) {
  return !(lhs.value() == rhs);
}

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
}
}
