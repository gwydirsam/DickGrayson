#include <iostream>
#include "rsa-attack-lib.h"

using namespace std;
vector<int> d_int;

//returns a vector of pairs that correspond to the found factors
vector<pair<mpz_class, mpz_class > > findFactors(mpz_class n){
  vector<pair< mpz_class, mpz_class> > factors;

  //trial division method...
   //ignore 0 and 1, since they're not valid factors
  for(mpz_class i = 2; (i*i) <= n; ++i) {

    if((n % i) == 0) {
      mpz_class first_factor = i;
      mpz_class other_factor = (n/i);
      //Do we want to keep 2 factors if they're the same? (i.e. 5*5)
      factors.push_back(pair<mpz_class, mpz_class>(first_factor, other_factor));
    }
  }

  return factors;
}
