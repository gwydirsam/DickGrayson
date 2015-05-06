#include "low_exponent.hh"

namespace lowexp {

  using namespace std;
  //for this attack to work, the message must be the same, exponent must be low
  mpz_class low_exponent_attack(rsatk::RSA_data m_1, rsatk::RSA_data m_2, rsatk::RSA_data m_3){
    //first check that attack is valid
    if(!lowexp_valid(m_1, m_2, m_3)){
      return -1;
    }
    mpz_class message_cubed = 0; //will be assigned in pow_ui

    //mpz_pow_ui(message_cubed, m_1.C, 3);
    //mod(m_cubed, m_2.n);
    //for an in depth discussion of these eqs..http://crypto.stackexchange.com/a/6715
    cout << rsatk::extended_euclidean(m_2.n * m_3.n, m_1.n)[0] << endl;

    mpz_class t_1 = mpz_class(m_1.C) * (m_2.n * m_3.n) * rsatk::extended_euclidean(m_2.n * m_3.n, m_1.n)[0];
    mpz_class t_2 = mpz_class(m_2.C) * (m_1.n * m_3.n) * rsatk::extended_euclidean(m_1.n * m_3.n, m_2.n)[0];
    mpz_class t_3 = mpz_class(m_3.C) * (m_2.n * m_1.n) * rsatk::extended_euclidean(m_2.n * m_1.n, m_3.n)[0];

    mpz_class c = rsatk::mod((t_1 + t_2 + t_3), (m_1.n * m_2.n * m_3.n));

    mpz_class m;
    mpz_root(m.get_mpz_t(), c.get_mpz_t(), 3);
    return m;
  }

  bool lowexp_valid(rsatk::RSA_data m_1, rsatk::RSA_data m_2, rsatk::RSA_data m_3){
    //if (m_1.C != m_2.C || m_1.C != m_3.C || m_1.C == -1) {
    //cerr << "Invalid message to use low exponent attack. All three messages must be the same." << endl;
    //return false;
    //}
    if(m_1.e != m_2.e || m_1.e != m_3.e || m_1.e != 3){
      cerr << "Invalid message to use low exponent attack. Must have an exponent of 3." << endl;
      return false;
    }
    return true;
  }
}
