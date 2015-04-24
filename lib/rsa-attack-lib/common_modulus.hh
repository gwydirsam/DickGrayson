#pragma once

#include "rsa-attack-lib.hh"
#include <rsa-crypt-lib/rsa-crypt-lib.hh>

namespace comodulus {
  mpz_class common_modulus_attack(rsatk::RSA_data m_1, rsatk::RSA_data m_2);
}

