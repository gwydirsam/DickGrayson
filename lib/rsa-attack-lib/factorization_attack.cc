#include "factorization_attack.hh"

namespace factoratk {
  // requires the following in RSA_data: C, n, and e.
  // All of these are obtainable from a public RSA key
  mpz_class factorization_attack(rsatk::RSA_data m_1){
    if(m_1.n == -1) {
      return -1;
    }

    std::pair<mpz_class, mpz_class> factors = rsatk::find_prime_factors(m_1.n);

    mpz_class totient = rsatk::calculate_totient(factors.first, factors.second);
    mpz_class d = rsatk::calculate_d(totient, m_1.e);

    //once decrypt is ready, this will be finished
    //string decrypted_message = rsatk::decrypt_message(encrypted_message, n, d);
    return 0;
  }
}
