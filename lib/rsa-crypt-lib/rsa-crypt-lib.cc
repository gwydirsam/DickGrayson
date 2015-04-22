#include "rsa-crypt-lib.hh"

#include <gmpxx.h>

#include <dgcrypto/dgcrypto.hh>
#include <iostream>

//to use 'random' is there more specific header?
#include <stdlib.h>

//always run with primes 512 bits big to make sure max value works
int NUM_BITS = 512;
mpz_class n = 0;
// generates two random primes and checks coprimality
mpz_class RsaKeys::generate_public_key(int num_bits) {
  //weird I know, just for testing
  num_bits = NUM_BITS;
 
  mpz_class p = dgrprime::generate_prime(NUM_BITS); 
  mpz_class q = dgrprime::generate_prime(NUM_BITS);

  std::cout << "VALUE_OF p is : " << p << std::endl;

  while (!is_coprime(p, q)) {
    q = dgrprime::generate_prime(NUM_BITS);
  }
  std::cout << "VALUE_OF q is : " << q << std::endl;
  n = compute_n(p,q);
  mpz_class tn = compute_theta_n(p,q);
  return p;
}

// helper function to check for primality
bool RsaKeys::is_coprime(mpz_class p, mpz_class q) {
  mpz_class gcd = 1;
  for (mpz_class i = 1; ((i <= p) && (i <= q)); ++i) {
    if ((p % i == 0) && (q % i == 0)) {
      gcd = i;
    }
  }

  return (gcd != 1) ? false : true;
}

// n = p*q
mpz_class RsaKeys::compute_n(mpz_class p, mpz_class q) { return (p * q); }

// theta n = (p-1)*(q-1)
mpz_class RsaKeys::compute_theta_n(mpz_class p, mpz_class q) {
  return ((p - 1) * (q - 1));
}

mpz_class RsaKeys::compute_e(mpz_class theta_n) {
  // TODO: check that 1<e<theta_n and check for primality to release exponent
  // value 'e'
  mpz_class e = generate_random_value();
  while(e < theta_n || !is_coprime(e, theta_n)){
    e = generate_random_value();
  }
  return e;
}

mpz_class RsaKeys::generate_random_value(){
  
  mpz_class value = 0;
  // initialize random engine (can't use our member in static function)
  gmp_randclass rand_engine{gmp_randinit_default};
  
  // seed gmp_rand_alg_ with a uint from random_device
  rand_engine.seed(std::random_device{}());


  //intitialize to first non prime number so while loop executes
  value = rand_engine.get_z_bits(NUM_BITS);

  return value;
}
