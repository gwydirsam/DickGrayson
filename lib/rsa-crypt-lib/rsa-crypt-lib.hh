#pragma once

#include <gmpxx.h>

class RsaCrypt {
 public:
  // generates two random primes and checks coprimality
  mpz_class generate_key();

  mpz_class compute_n(mpz_class p, mpz_class q);
  mpz_class compute_theta_n(mpz_class p, mpz_class q);

 private:
  // helper function to check for primality
  bool is_coprime(mpz_class value1, mpz_class value2);
};
