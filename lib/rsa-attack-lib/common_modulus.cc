#include "common_modulus.hh"
#include "../rsa-crypt-lib/base64.h"

namespace comodulus {

using namespace std;

// returns private key d
// this should take two ciphertexts...but what form does that come in?
// for now let's use large numbers
  mpz_class common_modulus_attack(rsatk::RSA_data m_1, rsatk::RSA_data m_2) {
  vector<mpz_class> ee_result = rsatk::extended_euclidean(m_1.e, m_2.e);

  if (m_1.n != m_2.n || ee_result[2] != 1 || m_1.n == -1) {
    cerr << "Common modulus won't work. Both n_1 and n_2 must be the same and "
            "gcd(e_1, e_2) must equal 1. " << endl;
    return -1;
  }
  mpz_class x = ee_result[0];
  mpz_class y = ee_result[1];
  mpz_class E(m_1.C);
  mpz_class F(m_2.C);

  mpz_class M_e1;
  mpz_class M_e2;
  mpz_class M;
  // mpz_pow_ui(M_e1.get_mpz_t(), E.get_mpz_t(), li_x);
  // mpz_pow_ui(M_e2.get_mpz_t(), F.get_mpz_t(), li_y);
  mpz_pow_ui(M_e1.get_mpz_t(), E.get_mpz_t(), mpz_get_si(x.get_mpz_t()));
  mpz_pow_ui(M_e2.get_mpz_t(), F.get_mpz_t(), mpz_get_si(y.get_mpz_t()));
  mpz_class product_M_e12 = (M_e1 * M_e2);
  mpz_powm_ui(M.get_mpz_t(), product_M_e12.get_mpz_t(), 1,
              m_1.n.get_mpz_t());  // mods by n and assigns to M

  // M is now the original message
  return M;
}

}
