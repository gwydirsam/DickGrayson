#include "rsa-attack-lib.hh"
// a known totient can yield the factors very quickly.
// this is admittedly a rare attack, but one we want to
// take advantage of if we get the opportunity

// finds p
mpz_class totient_attack(mpz_class totient, mpz_class n){
  mpz_class a = 1;
  mpz_class b = (n - totient + 1);
  mpz_class c = n;
  mpz_class b_squared;
  long int li_b = mpz_get_si(b.get_mpz_t());
  mpz_ui_pow_ui(b_squared.get_mpz_t(), li_b, 2);
  //quadratic eq where x is p
  mpz_class first_x = (b + sqrt(b_squared - 4 * a * c)) / (2 * a);
  mpz_class second_x = (b - sqrt(b_squared - 4 * a * c)) / (2 * a);

  if(first_x > 0) return first_x;
  return second_x;
}
