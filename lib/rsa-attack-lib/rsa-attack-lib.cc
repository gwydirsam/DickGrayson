#include <iostream>
#include <limits>
#include <string>
#include <cassert>
#include "rsa-attack-lib.hh"
#include <dgcrypto/dgcrypto.hh>
using namespace std;

//returns a vector of pairs that correspond to the found factors
vector<pair<mpz_class, mpz_class > > findPrimeFactors(mpz_class n){
  vector<pair< mpz_class, mpz_class> > factors;

  ifstream prime_file;
  prime_file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
  try{
    //assumption that we run the executable inside of top directory
    prime_file.open("lib/rsa-attack-lib/prime_list_1000000", ios::in);
  }
  catch (std::ifstream::failure e) {
    std::cerr << "Exception opening file..file not found\n";
    exit(EXIT_FAILURE);
  }

  //trial division method...
  mpz_class prime_candidate = 0;

  //ignore 0 and 1, since they're not valid factors
  while((prime_candidate * prime_candidate) <= n) {
    prime_candidate = getNextPrime(prime_file);

    if((n % prime_candidate) == 0) { //then it's a factor
      mpz_class first_factor = prime_candidate;
      mpz_class other_factor = (n/prime_candidate);

      if(dgrprime::is_prime(other_factor) && DG::Crypto::RandomPrime::is_prime(first_factor)){// then it's a prime
        factors.push_back(pair<mpz_class, mpz_class>(first_factor, other_factor));
        return factors;
      }
    }
  }

  return factors;
}


mpz_class getNextPrime(ifstream& prime_file){
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


//Note to TA:
//we don't actually use this in our tools,
//we only use it to generate a PrimeList file for later use
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

//deprecated past here...
//helper function
fstream& skipToLine(fstream& file, mpz_class line_num){
  for(int i=0; i < line_num; ++i){
    file.ignore(numeric_limits<streamsize>::max(),'\n');
  }
  return file;
}
