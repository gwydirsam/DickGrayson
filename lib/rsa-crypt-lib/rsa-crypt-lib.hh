#pragma once

#include "base64.h"
#include <gmpxx.h>
#include <tuple>  // std::tuple
#include <iostream>
#include <vector>

class RsaKeys {
 public:
  RsaKeys() : RsaKeys{512} {}
  RsaKeys(mp_bitcnt_t k);

  // accessors
  mpz_class n() { return n_; }
  unsigned int e() { return e_; }
  mpz_class totient() { return totient_; }
  mpz_class d() { return d_; }
  mp_bitcnt_t bits() { return bits_; }
  std::string encrypt_message(std::string message);
  std::string decrypt_message(std::string message);
  static std::string encrypt_message(std::string message, unsigned int e, mpz_class n);
  static std::string decrypt_message(std::string message, mpz_class d, mpz_class n);

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
  unsigned int compute_e(mpz_class totient);

  // get gcd
  const mpz_class get_gcd(mpz_class p, mpz_class q) const;

  //encrypts message
  static std::string encrypt(std::string message, unsigned int e, mpz_class n);

  //decrypts message using key
  static std::string decrypt(std::string cryptText, mpz_class d, mpz_class n);

  static std::string num_to_string(mpz_class num);
  static mpz_class string_to_num(std::string message);
  std::string decode(std::string);//decodes message from base_64 -> ascii
  std::string encode(std::string);//encodes message from ascii -> base_64

  // computer e (euclidean extended algorithm)
  mpz_class compute_d(mpz_class e, mpz_class totient);

  std::vector<mpz_class> extended_euclidean(mpz_class a, mpz_class b);

  mpz_class calculate_d(mpz_class totient, mpz_class e);

  mpz_class my_pow(mpz_class a, mpz_class b);

  static inline bool is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
  }

 private:
  // data members
  mpz_class n_;
  unsigned int e_;
  mpz_class totient_;
  mpz_class d_;
  mp_bitcnt_t bits_;

  // private member helper functions
  // helper function to check for primality
  inline bool is_coprime(mpz_class p, mpz_class q) const;
};
