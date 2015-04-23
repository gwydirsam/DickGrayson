#pragma once

#include <gmpxx.h>
#include <vector>
#include <iostream>
#include <utility>
#include <fstream>

//done in an intentionally procedural style. You can use any function independently
//names are according to RSA idioms
//p and q are the prime numbers, and n is their product
//m is the plain_test
namespace rsatk{
  std::vector<std::pair<mpz_class, mpz_class> > find_prime_factors(mpz_class n);
  void generate_n_primes(mpz_class n);

  //this function uses pre-cached prime_lists
  mpz_class get_next_prime(std::ifstream & prime_file);

  mpz_class calculate_totient(mpz_class p, mpz_class q);

  mpz_class calculate_d(mpz_class totient, mpz_class e);

  //extended_euclidean(a, b) returns three values:
  //x, y, gcd, such that ax + by = gcd(a, b)
  std::vector<mpz_class> extended_euclidean(mpz_class totient, mpz_class e);
  std::string decrypt_message(std::string encrypted,  mpz_class n, mpz_class d);

}
