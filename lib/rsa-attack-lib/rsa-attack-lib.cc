#include <iostream>
#include <limits>
#include <string>
#include <cassert>
#include "rsa-attack-lib.hh"
#include "../dgcrypto/dgrandomprime.hh"
using namespace std;

//ported here from dg_randomprime until Rafa fixes..
bool is_prime(mpz_class value) {
  int k = 1;
  if(value == k)
    return true;
  if(value == 3)
    return true;
  mpz_class s, d, b, e, x;

  for(s = 0, d = value-1; !(d && 1); s++){
    d >>= 1;
  }

  for(x = 1, b = k % value, e = d; e; e >>= 1) {
    if(e && 1){
      x = (x * b) % value;
    }
  }

  if(x == 1 || x == value-1){
    return true;
  }

  while( s-- > 1) {
    x = (x * x) % value;
    if ( x == 1){
      return false;
    }
    if( x == value-1) {
      return true;
    }
  }
  return false;
}

//returns a vector of pairs that correspond to the found factors
vector<pair<mpz_class, mpz_class > > findPrimeFactors(mpz_class n){
  vector<pair< mpz_class, mpz_class> > factors;

  //string name_of_file = findOrGeneratePrimes();
  fstream prime_file;
  prime_file.open("lib/rsa-attack-lib/prime_list_1000000", ios::in);
  //trial division method...
  //ignore 0 and 1, since they're not valid factors
  mpz_class i = 0;
  mpz_class prime_candidate = i;
  while((prime_candidate * prime_candidate) <= n) {
    prime_candidate = getNextPrime(prime_file, i);
    if((n % prime_candidate) == 0) {
      mpz_class first_factor = prime_candidate;
      mpz_class other_factor = (n/prime_candidate);
      if(is_prime(other_factor) && is_prime(first_factor)){
        factors.push_back(pair<mpz_class, mpz_class>(first_factor, other_factor));
        return factors;
      }

    }
    ++i;
  }

  return factors;
}

mpz_class getNthPrime(mpz_class n){
  fstream prime_file;
  prime_file.open("lib/rsa-attack-lib/prime_list_1000000", ios::in);
  skipToLine(prime_file, n);
  getNextPrime(prime_file, n);
}

mpz_class getNextPrime(fstream& prime_file, mpz_class n){
  mpz_class num = -1;
  prime_file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
  try{
    prime_file >> num;
  }
  catch (std::ifstream::failure e) {
    std::cerr << "Exception opening/reading/closing file\n";
    exit(EXIT_FAILURE);
  }
  return num;
}

//Note to TA, we don't actually use this in our tools, we only use it to generate a PrimeList file for later use
void generateNPrimes(long int n){
  ofstream prime_list_file;
  prime_list_file.open("prime_list_" + to_string(n));
  mpz_class prime;

  for(int i = 0; i < n; ++i){
    mpz_nextprime(prime.get_mpz_t(), prime.get_mpz_t());
    prime_list_file << prime << "\n";
  }
  prime_list_file.close();
}

fstream& skipToLine(fstream& file, mpz_class num){
  for(int i=0; i < num; ++i){
    file.ignore(numeric_limits<streamsize>::max(),'\n');
  }
  return file;
}
