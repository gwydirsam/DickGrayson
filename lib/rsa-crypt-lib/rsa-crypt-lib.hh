#pragma once

#include <gmpxx.h>

// sam: why is this a class? Or maybe it should be called PublicKey?
class PublicKey {
 public:
  // generates two random primes and checks coprimality
  mpz_class generate_key();

  //n = p*q
  mpz_class compute_n(mpz_class p, mpz_class q);

  //theta_n = (p-1)*(q-1)
  mpz_class compute_theta_n(mpz_class p, mpz_class q);

  //generates exponent (e) where 1 < e < theta_n and theta_n and e are coprime
  mpz_class compute_e(mpz_class theta_n);


 private:
  // helper function to check for primality
  bool is_coprime(mpz_class p, mpz_class q);

  // helper function to generate random numbers
  mpz_class generate_random_value();
};
