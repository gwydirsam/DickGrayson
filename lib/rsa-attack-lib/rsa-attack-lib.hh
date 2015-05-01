#pragma once

#include <gmpxx.h>

#include <vector>
#include <iostream>
#include <utility>
#include <fstream>

// done in an intentionally procedural style. You can use any function
// independently
// names are according to RSA idioms
// p and q are the prime numbers, and n is their product
// m is the plain_test
namespace rsatk {

  struct RSA_data {
    mpz_class C = -1;        // cipher text
    mpz_class n = -1;        // p*q
    mpz_class e = -1;        // exponent of pub key
    mpz_class p = -1;        // prime factor
    mpz_class q = -1;        // ''
    mpz_class totient = -1;  // (p - 1) * (q - 1)
  };

  static const std::string relative_path = "../../lib/rsa-attack-lib/";

  std::pair<mpz_class, mpz_class> find_prime_factors(mpz_class n);
  void generate_n_primes(mpz_class n);

  // this function uses pre-cached prime_lists
  mpz_class get_next_prime(std::ifstream& prime_file);

  mpz_class calculate_totient(mpz_class p, mpz_class q);

  mpz_class calculate_d(mpz_class totient, mpz_class e);

  mpz_class mod(mpz_class num, mpz_class modulo);

  // extended_euclidean(a, b) returns three values:
  // x, y, gcd, such that ax + by = gcd(a, b)
  std::vector<mpz_class> extended_euclidean(mpz_class totient, mpz_class e);
  std::string decrypt_message(std::string encrypted, mpz_class n, mpz_class d);

  RSA_data parse_rsa_file(std::fstream& fname);
}
