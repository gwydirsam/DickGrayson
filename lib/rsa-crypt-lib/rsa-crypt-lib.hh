#pragma once

#include <gmpxx.h>

// sam: why is this a class? Or maybe it should be called PublicKey?
class PublicKey {
 public:
  // generates two random primes and checks coprimality
  mpz_class generate_key();

  mpz_class compute_n(mpz_class p, mpz_class q);
  mpz_class compute_theta_n(mpz_class p, mpz_class q);

 private:
  // helper function to check for primality
  bool is_coprime(mpz_class p, mpz_class q);
};
