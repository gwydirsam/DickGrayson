#include "rsa-attack-lib.hh"

#include <iostream>

#include <limits>
#include <vector>
#include <string>
#include <utility>  // std::pair
#include <fstream>

#include <cstdlib>
#include <cassert>

#include <dgcrypto/dgcrypto.hh>

// iostream
using std::ios;
using std::ios_base;
using std::cout;
using std::cerr;
using std::to_string;
using std::streamsize;
// vector
using std::vector;
// string
using std::string;
// utility
using std::pair;
// cstdlib
using std::exit;
// fstream
using std::fstream;
using std::ofstream;
using std::ifstream;
// limits
using std::numeric_limits;

// returns a vector of pairs that correspond to the found factors
vector<pair<mpz_class, mpz_class>> findPrimeFactors(mpz_class n) {
  vector<pair<mpz_class, mpz_class>> factors;
  try {
    // string name_of_file = findOrGeneratePrimes();
    ifstream prime_file;
    prime_file.open("prime_list_1000000", ios::in);
    // trial division method...
    // ignore 0 and 1, since they're not valid factors

    // while ((prime_candidate * prime_candidate) <= n) {
    // sam: use a for loop for indicies
    for (mpz_class i = 0, prime_candidate = 0;
         (prime_candidate * prime_candidate) <= n; ++i) {
      prime_candidate = getNextPrime(prime_file, i);
      if ((n % prime_candidate) == 0) {
        mpz_class first_factor = prime_candidate;
        mpz_class other_factor = (n / prime_candidate);
        if (dgrprime::is_prime(other_factor) &&
            dgrprime::is_prime(first_factor)) {
          factors.push_back(
              pair<mpz_class, mpz_class>(first_factor, other_factor));
          return factors;
        }
      }
      // sam: use a for loop for indicies
      // ++i;
    }
  } catch (ios_base::failure& e) {
    cerr << "Caught ios_base::failure: " << __PRETTY_FUNCTION__ << "\n";
    cerr << "Exception: " << e.what() << "\n";
    cerr << "Error Code: " << e.code() << "\n";
  }
  return factors;
}

mpz_class getNthPrime(mpz_class n) {
  // sam: find a way to get the file open, then move all operations inside the
  //      try-catch.
  //      catch only catches inside the try block.
  try {
    ifstream prime_file;
    prime_file.exceptions(ifstream::failbit | ifstream::badbit);
    prime_file.open("prime_list_1000000", ios::in);
    skipToLine(prime_file, n);
    getNextPrime(prime_file, n);
  } catch (ios_base::failure& e) {
    // } catch (ifstream::failure e) {
    // cerr << "Exception opening/reading/closing file\n";

    // sam: changed exception to a reference and you should cerr e.what() also
    // sam: also this is where you throw in every test
    cerr << "Caught ios_base::failure: " << __PRETTY_FUNCTION__ << "\n";
    cerr << "Exception: " << e.what() << "\n";
    cerr << "Error Code: " << e.code() << "\n";
    // sam: are you really sure you want to abort? I always thought catching
    // exceptions was in order to not just abort
    // exit(EXIT_FAILURE);
  }
  // you never return here!
  // do you want return getNextPrime?
}

// sam: what is mpz_class n there for? You get a warning that it's unused
// also you return a num but never use it
mpz_class getNextPrime(ifstream& prime_file, mpz_class n) {
  mpz_class num = -1;
  // sam: this goes in the try block
  // prime_file.exceptions(ifstream::failbit | ifstream::badbit);
  try {
    prime_file.exceptions(ifstream::failbit | ifstream::badbit);
    prime_file >> num;
  } catch (ios_base::failure& e) {
    // } catch (ifstream::failure e) {
    // cerr << "Exception opening/reading/closing file\n";

    // sam: changed exception to a reference and you should cerr e.what() also
    // sam: also this is where you throw in every test
    // cerr << "Exception opening/reading/closing file: " << e.what() <<
    // "\n";
    cerr << "Caught ios_base::failure: " << __PRETTY_FUNCTION__ << "\n";
    cerr << "Exception: " << e.what() << "\n";
    cerr << "Error Code: " << e.code() << "\n";
    exit(EXIT_FAILURE);
  }
  return num;
}

// sam: if this is the case -- maybe we should have it in a seperate binary?
//      I'll do it if you say the word.
// Note to TA, we don't actually use this in our tools, we only use it to
// generate a PrimeList file for later use
void generateNPrimes(long int n) {
  try {
    ofstream prime_list_file;
    prime_list_file.open("prime_list_" + to_string(n));
    mpz_class prime;

    // sam: n is a long int, i should be too
    for (long int i = 0; i < n; ++i) {
      mpz_nextprime(prime.get_mpz_t(), prime.get_mpz_t());
      prime_list_file << prime << "\n";
    }
    prime_list_file.close();
  } catch (ios_base::failure& e) {
    cerr << "Caught ios_base::failure: " << __PRETTY_FUNCTION__ << "\n";
    cerr << "Exception: " << e.what() << "\n";
    cerr << "Error Code: " << e.code() << "\n";
  }
}

ifstream& skipToLine(ifstream& file, mpz_class num) {
  try {
    // sam: num is an mpz_class, i should be too
    for (mpz_class i = 0; i < num; ++i) {
      file.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  } catch (ios_base::failure& e) {
    cerr << "Caught ios_base::failure: " << __PRETTY_FUNCTION__ << "\n";
    cerr << "Exception: " << e.what() << "\n";
    cerr << "Error Code: " << e.code() << "\n";
  }
  return file;
}
