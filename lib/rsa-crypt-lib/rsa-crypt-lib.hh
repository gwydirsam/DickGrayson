#pragma once

#include <gmpxx.h>

class PublicKey {
 public:
  PublicKey() : bits_(512) {}
  PublicKey(mp_bitcnt_t k) : bits_(k) {}

  // generates two random primes and checks coprimality
  mpz_class generate_key() const;

  // n = p*q
  inline mpz_class compute_n(mpz_class p, mpz_class q) const { return (p * q); }

  // theta_n = (p-1)*(q-1)
  inline mpz_class compute_theta_n(mpz_class p, mpz_class q) const {
    return ((p - 1) * (q - 1));
  }

  // generates exponent (e) where 1 < e < theta_n and theta_n and e are coprime
  mpz_class compute_e(mpz_class theta_n) const;

  // helper function to check for primality
  mpz_class get_gcd(mpz_class p, mpz_class q) const;

 private:
  // data members
  mp_bitcnt_t bits_;

  // private member helper functions
  // helper function to check for primality
  inline bool is_coprime(mpz_class p, mpz_class q) const;

  // helper function to generate random numbers
  mpz_class generate_random_value() const;
};
