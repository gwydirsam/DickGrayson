#pragma once

#include <gmpxx.h>
#include <vector>
#include <utility>
#include <fstream>

std::vector<std::pair<mpz_class, mpz_class> > findFactors(mpz_class n);
void generateNPrimes(long int n);
std::fstream& skipToLine(std::fstream& file, mpz_class num);
mpz_class getNthPrime(mpz_class n);
