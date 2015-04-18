#include "dgrandomprime.hh"

#include <gmpxx.h>
#include <iostream>
#include <random>

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
  } else {
    return true;
  }
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
  if ((value == 2) || (value == 3)) {
    // if value is 2 or 3, just return true they're not worth the time
    return true;
  } else if ((value < 2) || (value % 2 == 0)) {
    // if value is less than 2 or even return false
    return false;
  } else {
    // initialize random engine (can't use our member in static function)
    gmp_randclass rand_engine{gmp_randinit_default};
    // seed gmp_rand_alg_ with a uint from random_device
    rand_engine.seed(std::random_device{}());

    // sam: what does 's' mean?
    mpz_class s = value - 1;
    while (s % 2 == 0) {
      s /= 2;
    }

    // sam: why is this 5?
    mpz_class iteration = 5;

    for (mpz_class i = 0; i < iteration; i++) {
      // mpz_class a = rand() % (value - 1) + 1, temp = s;
      // sam: - don't use c rand, use gmp's random in this case
      //        else use c++ <random>
      //      - need a good value for base, not really sure what is good
      //      - what does 'a' mean?
      mpz_class a = rand_engine.get_z_range(5000000_mpz) % (value - 1) + 1;
      mpz_class temp = s;
      mpz_class mod = modulo(a, temp, value);

      while ((temp != value - 1) && (mod != 1) && (mod != value - 1)) {
        mod = mulmod(mod, mod, value);
        temp *= 2;
      }
      if ((mod != value - 1) && (temp % 2 == 0)) {
        return false;
      }
      // sam: could we do a 'else return true' here?....
    }
    // sam: ...instead of here
    return true;
  }
}

// return random prime of ~k bits
mpz_class RandomPrime::generate_prime(mp_bitcnt_t k) {
  // initialize random engine (can't use our member in static function)
  gmp_randclass rand_engine{gmp_randinit_default};
  // seed gmp_rand_alg_ with a uint from random_device
  rand_engine.seed(std::random_device{}());

  // sam: why do you set this to 4?
  mpz_class value = 4;

  while (!is_prime(value)) {
    value = rand_engine.get_z_bits(k);
  }

  return value;
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
