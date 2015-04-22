#pragma once

#include <gmpxx.h>
#include <vector>
#include <utility>
#include <fstream>

//done in an intentionally procedural style. You can use any function independently
//names are according to RSA idioms
//p and q are the prime numbers, and n is their product
//m is the plain_test
namespace rsatk{
  std::vector<std::pair<mpz_class, mpz_class> > findPrimeFactors(mpz_class n);
  void generateNPrimes(long int n);

  //this function is faster since you can hold onto your place
  //where n is the file offset
  mpz_class getNextPrime(std::ifstream & prime_file);

  mpz_class calculate_totient(mpz_class p, mpz_class q);
  mpz_class calculate_d(mpz_class totient, mpz_class e);
  mpz_class extended_euclidean(mpz_class totient, mpz_class e);

  std::string decrypt_message(std::string encrypted,  mpz_class n, mpz_class d);

}
