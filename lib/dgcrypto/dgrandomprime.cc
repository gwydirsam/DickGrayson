#include "dgrandomprime.hh"

#include <iostream>

namespace DG {
namespace Crypto {

// are the two values coprime
bool RandomPrime::is_coprime(mpz_class value1, mpz_class value2) {
  int gcd = 1;
  for (int i = 1; i <= value1 && i <= value2; i++) {
    if (value1 % i == 0 && value2 % i == 0) {
      gcd = i;
    }
  }
  if (gcd != 1) {
    return false;
  }

  return true;
}

// helper for is_prime
mpz_class RandomPrime::mulmod(mpz_class a, mpz_class b, mpz_class mod) {
  mpz_class x = 0, y = a % mod;
  while (b > 0) {
    if (b % 2 == 1) {
      x = (x + y) % mod;
    }
    y = (y * 2) % mod;
    b /= 2;
  }
  return x % mod;
}
// helper for is_prime
mpz_class RandomPrime::modulo(mpz_class base, mpz_class exponent,
                              mpz_class mod) {
  mpz_class x = 1;
  mpz_class y = base;
  while (exponent > 0) {
    if (exponent % 2 == 1) x = (x * y) % mod;
    y = (y * y) % mod;
    exponent = exponent / 2;
  }
  return x % mod;
}
// is value prime
bool RandomPrime::is_prime(mpz_class value) {
  mpz_class iteration = 5;
  if (value < 2) {
    return false;
  }
  if (value != 2 && value % 2 == 0) {
    return false;
  }
  mpz_class s = value - 1;
  while (s % 2 == 0) {
    s /= 2;
  }
  for (mpz_class i = 0; i < iteration; i++) {
    mpz_class a = rand() % (value - 1) + 1, temp = s;
    mpz_class mod = modulo(a, temp, value);
    while (temp != value - 1 && mod != 1 && mod != value - 1) {
      mod = mulmod(mod, mod, value);
      temp *= 2;
    }
    if (mod != value - 1 && temp % 2 == 0) {
      return false;
    }
  }
  return true;
}

// set value_ to prime of ~k bits
mpz_class RandomPrime::generate_prime(mp_bitcnt_t k) {
  this->value_ = gmp_rand_alg_.get_z_bits(k);
  return this->value_;
}

//// friend non-member operators
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
