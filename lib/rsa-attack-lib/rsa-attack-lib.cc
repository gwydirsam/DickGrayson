#include "rsa-attack-lib.hh"
#include <dgcrypto/dgcrypto.hh>
#include <iostream>
#include <vector>
namespace rsatk{
using namespace std;
string relative_path = "../../lib/rsa-attack-lib/";
  //returns a vector of pairs that correspond to the found factors
  vector<pair<mpz_class, mpz_class > > find_prime_factors(mpz_class n){
    vector<pair< mpz_class, mpz_class> > factors;

    ifstream prime_file;
    prime_file.exceptions ( ifstream::failbit | ifstream::badbit );
    try{
      //assumption that we run the executable inside of top directory
      prime_file.open(relative_path + "prime_list_1000000", ios::in);
    }
    catch (ifstream::failure e) {
      cerr << "Caught ios_base::failure: " << __PRETTY_FUNCTION__ << "\n";
      cerr << "Exception: " << e.what() << "\n";
      return factors;
    }

    //trial division method...
    mpz_class prime_candidate = 0;

    //ignore 0 and 1, since they're not valid factors
    while((prime_candidate * prime_candidate) <= n) {
      prime_candidate = get_next_prime(prime_file);

      if((n % prime_candidate) == 0) { //then it's a factor
        mpz_class first_factor = prime_candidate;
        mpz_class other_factor = (n/prime_candidate);

        if(dgrprime::is_prime(other_factor) && dgrprime::is_prime(first_factor)){// then it's a prime factor
          factors.push_back(pair<mpz_class, mpz_class>(first_factor, other_factor));
          return factors;
        }
      }
    }
    return factors;
  }


  mpz_class get_next_prime(ifstream& prime_file){
    mpz_class num = -1;
    try {
      prime_file.exceptions(ifstream::failbit | ifstream::badbit);
      prime_file >> num;
    } catch (ios_base::failure& e) {
      cerr << "Caught ios_base::failure: " << __PRETTY_FUNCTION__ << "\n";
      cerr << "Exception: " << e.what() << "\n";
    }
    return num;
  }

  void generate_n_primes(long int n) {
    try {
      fstream prime_list_file;
      prime_list_file.open(relative_path + "prime_list_" + to_string(n));
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
    }
  }

  //deprecated past here...
  //helper function
  fstream& skipToLine(fstream& file, mpz_class line_num){
    try {

      for(int i=0; i < line_num; ++i){
        file.ignore(numeric_limits<streamsize>::max(),'\n');
      }

    }
    catch (ios_base::failure& e) {
      cerr << "Caught ios_base::failure: " << __PRETTY_FUNCTION__ << "\n";
    }
    return file;
  }

  //not implemented yet
  mpz_class calculate_totient(mpz_class p, mpz_class q){
    return (p-1) * (q-1);
  }
  mpz_class calculate_d(mpz_class totient, mpz_class e){
    //we want the second value: y
    mpz_class d = extended_euclidean(totient, e)[1];
    //make sure d is in our bounds

    mpz_class bounded_d = d % totient;

    //C++ mod arithmetic not suitable if d is negative
    //http://stackoverflow.com/a/12089637
    if(bounded_d < 0){
      bounded_d = bounded_d + totient;
    }

    return bounded_d;
  }

  vector<mpz_class> extended_euclidean(mpz_class a, mpz_class b){
    vector<mpz_class> x_y_gcd(3);

    mpz_class x, last_x, y, last_y, r, last_r;
    x =  last_y = 0;
    y = last_x = 1;
    r = b;
    last_r = a;
    while(r != 0){
      mpz_class q = last_r / r; //floor division because of int type
      //mpz_class r = b % a;
      mpz_class tmp = r;
      r = last_r - q * tmp;
      last_r = tmp;

      tmp = x;
      x = last_x - q * tmp;
      last_x = tmp;

      tmp = y;
      y = last_y - q * tmp;
      last_y = tmp;
    }
    x_y_gcd = {last_x, last_y, last_r};
    return x_y_gcd;
  }

  std::string decrypt_message(std::string encrypted,  mpz_class n, mpz_class d){return "not implemented";}
}
