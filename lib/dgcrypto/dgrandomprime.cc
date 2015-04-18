#include "dgrandomprime.hh"

#include <iostream>

namespace DG {
namespace Crypto {

//are the two values coprime
bool RandomPrime::is_coprime(mpz_class value1, mpz_class value2){
  int gcd = 1;
  for(int i = 1; i<= value1 && i <= value2; i++){
    if(value1 % i == 0 && value2 %i == 0){
      gcd = i;
    }
  }
  if(gcd != 1){
    return false;
  } 
  
  return true;
}
// is value prime
bool RandomPrime::is_prime(mpz_class value) {
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

// set value_ to prime of ~k bits
mpz_class RandomPrime::generate_prime(mp_bitcnt_t k) {
  this->value_ = gmp_rand_alg_.get_z_bits(k);
  return this->value_;
}

//// friend non-member operators
std::ostream& operator<<(std::ostream& os,
                         const DG::Crypto::RandomPrime& random_prime) {
  os << random_prime.value_;
  return os;
}

std::istream& operator>>(std::istream& is,
                         DG::Crypto::RandomPrime& random_prime) {
  // read in bits followed by value
  is >> random_prime.bits_ >> random_prime.value_;

  // figure out how to decide if this construction is invalid
  // if () is.setstate(std::ios::failbit);
  return is;
}
}
}
