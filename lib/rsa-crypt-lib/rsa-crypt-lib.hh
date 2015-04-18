#pragma once

#include <gmpxx.h>

class RsaCrypt {
  public:
    static mpz_class generate_key();
    static mpz_class compute_n(mpz_class p, mpz_class q);
    static mpz_class compute_theta_n(mpz_class p, mpz_class q);

  private:
  	static bool is_coprime(mpz_class value1, mpz_class value2);

};
