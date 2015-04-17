#include <iostream>
#include <limits>
#include <string>
#include <cassert>
#include "rsa-attack-lib.hh"
#include "dgrandomprime.hh"
using namespace std;


//returns a vector of pairs that correspond to the found factors
vector<pair<mpz_class, mpz_class > > findPrimeFactors(mpz_class n){
  vector<pair< mpz_class, mpz_class> > factors;

  //trial division method...
   //ignore 0 and 1, since they're not valid factors
  mpz_class i = 0;
  mpz_class prime_candidate = i;
  while((prime_candidate * prime_candidate) <= n) {
    prime_candidate = getNthPrime(i);
    if((n % prime_candidate) == 0) {
      mpz_class first_factor = prime_candidate;
      mpz_class other_factor = (n/prime_candidate);
      //Do we want to keep 2 factors if they're the same? (i.e. 5*5)
      factors.push_back(pair<mpz_class, mpz_class>(first_factor, other_factor));
    }
    ++i;
  }

  return factors;
}

mpz_class getNthPrime(mpz_class n){
  mpz_class num = -1;
  fstream prime_file;
  prime_file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
  try{
    prime_file.open("lib/rsa-attack-lib/prime_list_1000000", ios::in);
    skipToLine(prime_file, n);
    prime_file >> num;
    cout << num << endl;
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
  file.seekg (0, file.end);
  int length = file.tellg();
  file.seekg (0, file.beg);
  //file.seekg(ios::beg);
  assert(num < length);
  if(num > length){
    cout << "Asserts are'nt working";
  }
  for(int i=0; i < num; ++i){
    file.ignore(numeric_limits<streamsize>::max(),'\n');
  }
  return file;
}
