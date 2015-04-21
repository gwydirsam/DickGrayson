#pragma once

#include <gmpxx.h>
#include <vector>
#include <utility>
#include <fstream>

std::vector<std::pair<mpz_class, mpz_class> > findPrimeFactors(mpz_class n);
void generateNPrimes(long int n);

//this function is faster since you can hold onto your place
//where n is the file offset
mpz_class getNextPrime(std::ifstream & prime_file);
