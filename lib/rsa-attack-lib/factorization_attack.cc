#include "factorization_attack.hh"
#include <rsa-crypt-lib/rsa-crypt-lib.hh>

namespace factoratk {
  // requires the following in RSA_data: C, n, and e.
  // All of these are obtainable from a public RSA key
  mpz_class factorization_attack(rsatk::RSA_data m_1){
    if(m_1.n == -1) {
      std::cout << "Unable to decrypt due to improper data..." << std::endl;
      return -1;
    }

    std::pair<mpz_class, mpz_class> factors = rsatk::find_prime_factors(m_1.n);

    mpz_class totient = rsatk::calculate_totient(factors.first, factors.second);
    mpz_class d = rsatk::calculate_d(totient, m_1.e);

    std::cout << "P = " << factors.first << " | " << " Q = " << factors.second << std::endl;
    std::cout << "totient = " << totient << " | " << " private key = " << d << std::endl;

    if(m_1.C.size() >= 1){
      std::cout << "Original message was: " << RsaKeys::decrypt_message(m_1.C, d, m_1.n) << std::endl;
    }


    //once decrypt is ready, this will be finished
    //string decrypted_message = rsatk::decrypt_message(encrypted_message, n, d);
    return 0;
  }
}
