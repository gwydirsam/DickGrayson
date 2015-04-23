#pragma once

#include <gmpxx.h>
#include <tuple>  // std::tuple
#include <iostream>

class RsaKeys {
 public:
  RsaKeys() : RsaKeys{512} {}
  RsaKeys(mp_bitcnt_t k);

  // accessors
  mpz_class n() { return n_; }
  mpz_class e() { return e_; }
  mpz_class totient() { return totient_; }
  mp_bitcnt_t bits() { return bits_; }

  // generates two random primes and checks coprimality
  // mpz_class generate_key() const;
  const std::tuple<mpz_class, mpz_class> generate_keys() const;

  // n = p*q
  inline const mpz_class compute_n(mpz_class p, mpz_class q) const {
    return (p * q);
  }

  // theta_n = (p-1)*(q-1)
  inline const mpz_class compute_totient(mpz_class p, mpz_class q) const {
    return ((p - 1) * (q - 1));
  }

  // generates exponent (e) where 1 < e < theta_n and theta_n and e are coprime
  const mpz_class compute_e(mpz_class totient) const;

  // get gcd
  const mpz_class get_gcd(mpz_class p, mpz_class q) const;

  //computer e (euclidean extended algorithm)
  const mpz_class compute_d(mpz_class e, mpz_class totient) const;

 private:
  // data members
  mpz_class n_;
  mpz_class e_;
  mpz_class totient_;
  mp_bitcnt_t bits_;

  // private member helper functions
  // helper function to check for primality
  inline bool is_coprime(mpz_class p, mpz_class q) const;
};
