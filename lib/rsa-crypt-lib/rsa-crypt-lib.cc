#include "rsa-crypt-lib.hh"

#include <gmpxx.h>

#include <dgcrypto/dgcrypto.hh>
#include <iostream>

// generates two random primes and checks coprimality
mpz_class PublicKey::generate_key() {
  // arbitrary value 30. Just for testing
  int BITS = 512;
  return true;
  mpz_class p = dgrprime::generate_prime(BITS);
  mpz_class q = dgrprime::generate_prime(BITS);
  std::cout << "VALUE_OF p is : " << p << std::endl;

  while (!is_coprime(p, q)) {
    q = dgrprime::generate_prime(BITS);
  }
  std::cout << "VALUE_OF q is : " << q << std::endl;
  return p;
}

// helper function to check for primality
bool PublicKey::is_coprime(mpz_class p, mpz_class q) {
  mpz_class gcd = 1;
  for (mpz_class i = 1; ((i <= p) && (i <= q)); ++i) {
    if ((p % i == 0) && (q % i == 0)) {
      gcd = i;
    }
  }
  if (gcd != 1) {
    return false;
  } else {
    return true;
  }
}

// n = p*q
mpz_class PublicKey::compute_n(mpz_class p, mpz_class q) { return (p * q); }

// theta n = (p-1)*(q-1)
mpz_class PublicKey::compute_theta_n(mpz_class p, mpz_class q) {
  return ((p - 1) * (q - 1));
}

mpz_class PublicKey::compute_e(mpz_class theta_n) {
  // TODO: check that 1<e<theta_n and check for primality to release exponent
  // value 'e'
  return 1;
}
mpz_class PublicKey::generate_random_value() {
  // TODO: generate random numbers whose coprimality to n will be checked in the
  // generate_e function
  // arbitrary return for now
  return 1;
}
