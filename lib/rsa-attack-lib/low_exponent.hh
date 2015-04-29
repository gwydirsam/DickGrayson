#pragma once

#include "rsa-attack-lib.hh"
#include <rsa-crypt-lib/rsa-crypt-lib.hh>

namespace lowexp {
  mpz_class low_exponent_attack(rsatk::RSA_data m_1, rsatk::RSA_data m_2, rsatk::RSA_data m_3);
}
