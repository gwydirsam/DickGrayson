#pragma once

#include <vector>
#include <utility>
#include <fstream>

#include <gmpxx.h>

// sam: this stuff should really be a class -- otherwise you have to understand
//      your implementation to use these functions without doing something you
//      do not want.
//      notably, you open a file and close it in different functions
//      maybe in the class version open in the constructor and close in the
//      destructor? (not totally sure that is good advice)
//      I've also left some comments in the cc
//      I also moved you to using std::blah, and removed all std:: from the file
//
// TODO:
//      - [ ] put in class (or atleast a namespace, these shouldn't be global)
//      - [ ] fix exceptions
//      - [ ] dedicate to either writing std or using std::blah, a mix is hard to
//            read
std::vector<std::pair<mpz_class, mpz_class>> findPrimeFactors(mpz_class n);

void generateNPrimes(long int n);

std::ifstream& skipToLine(std::ifstream& file, mpz_class num);

mpz_class getNthPrime(mpz_class n);

mpz_class getNextPrime(
    std::ifstream& prime_file,
    mpz_class n);  // this function is faster since you can hold onto your place
