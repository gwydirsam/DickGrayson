#pragma once

#include <gmpxx.h>

struct DGPrime {
  // disable default constructor
  DGPrime() = delete;
  DGPrime(unsigned int k) : bits_{k} {}

  void bits(unsigned int bits) { bits_ = bits; }
  unsigned int bits() const { return bits_; }

  // number of bits
  unsigned int bits_;
};
