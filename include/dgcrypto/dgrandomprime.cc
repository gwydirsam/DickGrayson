#include "dgprime.hh"

#include <iostream>

std::ostream& operator<<(std::ostream& os, const DG::RandomPrime& random_prime) {
  os << random_prime.value_;
  return os;
}

std::istream& operator>>(std::istream& is, DG::RandomPrime& random_prime) {
  // read in bits followed by value
  unsigned int bits;
  mpz_class value;
  is >> bits >> value;
  random_prime.bits(bits);
  random_prime.value(value);

  // figure out how to decide if this construction is invalid
  // if () is.setstate(std::ios::failbit);
  return is;
}
