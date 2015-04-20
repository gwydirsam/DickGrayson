#include "rsa-crypt-lib.hh"

#include <gmpxx.h>

#include <dgcrypto/dgcrypto.hh>

// generates two random primes and checks coprimality
mpz_class PublicKey::generate_key() {
  // sam: why are these set to 30?
  mpz_class p = dgrprime::generate_prime(30);
  mpz_class q = dgrprime::generate_prime(30);

  while (!is_coprime(p, q)) {
    q = dgrprime::generate_prime(30);
  }

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

mpz_class PublicKey::compute_n(mpz_class p, mpz_class q) { return (p * q); }

mpz_class PublicKey::compute_theta_n(mpz_class p, mpz_class q) {
  return ((p - 1) * (q - 1));
}
