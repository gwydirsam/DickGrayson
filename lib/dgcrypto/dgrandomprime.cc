#include "dgrandomprime.hh"

#include <gmpxx.h>
#include <iostream>
#include <random>

namespace DG {
namespace Crypto {

// are the two values coprime
bool RandomPrime::is_coprime(mpz_class value1, mpz_class value2) {
  // sam: these all have to be mpz_class
  mpz_class gcd = 1;
  for (mpz_class i = 1; i <= value1 && i <= value2; ++i) {
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
  // sam: what are any of these one letter variables?
  mpz_class x = 0, y = a % mod;
  while (b > 0) {
    if (is_odd(b)) {
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
  // sam: what are any of these one letter variables?
  mpz_class x = 1;
  mpz_class y = base;

  while (exponent > 0) {
    if (is_odd(exponent)) {
      x = (x * y) % mod;
    }
    y = (y * y) % mod;
    exponent = exponent / 2;
  }
  return x % mod;
}

// is value prime
bool RandomPrime::is_prime(mpz_class value) {
  if (value == 2) {
    // base case
    return true;
  } else if ((value < 2) || is_even(value)) {
    // if value is less than 2 or even return false
    return false;
  } else {
    // http://www.cppsamples.com/common-tasks/unpredictable-random-numbers.html
    std::random_device rand_d;
    std::seed_seq seed_seq{rand_d(), rand_d(), rand_d(),
                           rand_d(), rand_d(), rand_d()};
    std::mt19937 mt_engine{seed_seq};

    // initialize random engine (can't use our member in static function)
    gmp_randclass rand_engine{gmp_randinit_default};
    // seed gmp_rand_alg_ with a uint from random_device
    rand_engine.seed(mt_engine());

    // sam: what are any of these one letter variables?
    // sam: what does 's' mean?
    mpz_class s = value - 1;
    while (is_even(s)) {
      s /= 2;
    }

    // sam: why is this 5?
    static const mpz_class iteration = 5;

    for (mpz_class i = 0; i < iteration; ++i) {
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
      if ((mod != value - 1) && (is_even(temp))) {
        return false;
      } else {
        return true;
      }
    }
  }
  // nothing should manage to reach this, but it's definitly not prime then.
  return false;
}

// return random prime of ~k bits
mpz_class RandomPrime::generate_prime(mp_bitcnt_t k) {
  // http://www.cppsamples.com/common-tasks/unpredictable-random-numbers.html
  std::random_device rand_d;
  std::seed_seq seed_seq{rand_d(), rand_d(), rand_d(),
                         rand_d(), rand_d(), rand_d()};
  std::mt19937 mt_engine{seed_seq};

  // initialize random engine (can't use our member in static function)
  gmp_randclass rand_engine{gmp_randinit_default};
  // seed gmp_rand_alg_ with a uint from random_device
  rand_engine.seed(mt_engine());

  // intitialize to first non prime number so while loop executes
  mpz_class value = 4;

  while (!is_prime(value)) {
    value = rand_engine.get_z_bits(k);
  }

  return value;
}
}
}
