#include "base64.h"
#include "rsa-crypt-lib.hh"
#include "../rsa-attack-lib/rsa-attack-lib.hh"

#include <gmpxx.h>

#include <vector>
#include <cassert>
#include <sstream>
#include <iostream>
#include <tuple>      // std::tuple
#include <algorithm>  // std::min
#include <bitset>
#include <fstream>
#include <dgcrypto/dgcrypto.hh>


//temp until we get linking in order


// to use 'random' is there more specific header?
// I meant #include <random> for std::random_device
// #include <random>
// sam: don't need this if we use dgrandprime

// generates two random primes and checks coprimality
RsaKeys::RsaKeys(mp_bitcnt_t k) : bits_{k}  {
  // generate p and q
  std::tuple<mpz_class, mpz_class> keys = generate_keys();
  mpz_class q = std::get<0>(keys);
  mpz_class p = std::get<1>(keys);

  // compute n
  this->n_ = compute_n(p, q);
  // compute totient
  this->totient_ = compute_totient(p, q);
  // compute e
  this->e_ = compute_e(this->totient_);
  // compute d
  this->d_ = calculate_d(totient_, e_);
  // public key
  // private key
  // std::cerr<<"Public key is : "<<p<<q<<d_<<std::endl;
  std::ofstream key_file;
  key_file.open("keys.txt"); 
  key_file<<"Public key : "<<p<<q<<d_<<std::endl;
  key_file<<"Private key: "<<n_<<e_<<std::endl;
  key_file.close();
}


std::string RsaKeys::num_to_string(mpz_class num){
  char * tmp = mpz_get_str(NULL, 10, num.get_mpz_t());
  std::string num_str = tmp;
  assert(num_str[0] == '1');
  num_str.erase(0, 1); //take off padding guard.

  const int CHAR_LENGTH = 3;
  std::string new_str = "";
  //takes out three digit numbers and cast to char
  for(std::size_t i = 0; i < num_str.size(); i+=CHAR_LENGTH){
    assert(num_str.size() > i+2);

    char c = (char)(stoi(num_str.substr(i, CHAR_LENGTH)));
    new_str.insert(0, 1, c);
  }
  return new_str;
}

mpz_class RsaKeys::string_to_num(std::string message){
  std::string num_str = "";
  for (std::size_t i = 0; i < message.size(); ++i)
    {
      std::string msg_int = std::to_string((int)message[i]);
      while(msg_int.size() < 3){//all nums should be three bit width
        msg_int = "0" + msg_int;
      }
      num_str.insert(0, msg_int); //will need to be reversed
    }

  std::string rev = num_str;
  rev = "1" + rev; //first num is to protect our padding
  mpz_class number_output(rev, 10);
  return number_output;
}

std::string decode(std::string){return "just a stub";}
std::string encode(std::string){return "just a stub";}


std::string RsaKeys::encrypt_message(std::string message) {
  return encrypt_message(message, e_, n_);
}
std::string RsaKeys::encrypt_message(std::string message, unsigned int e, mpz_class n){
  std::string split_msg = "";
  std::string full_msg = encrypt(message.substr(0, 100), e, n);
  //if the message is longer than 100, we'll delimit it with '-'s

  for(std::size_t i = 100; i < message.size(); i+=100){
    split_msg = message.substr(i, 100);
    full_msg += '-' + encrypt(split_msg, e, n);
  }
  //may lose a char to the null char size increase?
  std::string b64_msg = base64_encode(full_msg.c_str(), full_msg.size());
  return b64_msg;
}

std::string RsaKeys::decrypt_message(std::string message, mpz_class d, mpz_class n){
  std::string b10_msg = base64_decode(message);
  std::stringstream ss(b10_msg);
  std::string split_msg = "";
  std::string full_msg = "";
  while(getline(ss, split_msg, '-')){
    full_msg += decrypt(split_msg, d, n);
  }

  return full_msg;
}
std::string RsaKeys::decrypt_message(std::string message){
  return decrypt_message(message, d_, n_);
}


//encodes message
std::string RsaKeys::encrypt(std::string message, unsigned int e, mpz_class n) {
  mpz_class m = string_to_num(message);
  mpz_class encrypted_msg;
  mpz_pow_ui(encrypted_msg.get_mpz_t(), m.get_mpz_t(), e);
  encrypted_msg = dgcrypto::mod(encrypted_msg, n);
  //return num_to_string(encrypted_msg);
  return(mpz_get_str(NULL, 10, encrypted_msg.get_mpz_t()));
}


std::string RsaKeys::decrypt(std::string cryptText, mpz_class d, mpz_class n){
  mpz_class m(cryptText, 10);
  mpz_class decrypted_msg;
  //TODO: this is deprecated. We need to somehow cast d to an ui...
  mpz_powm_sec(decrypted_msg.get_mpz_t(), m.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());

  return num_to_string(decrypted_msg);
}


// helper function to check for primality
// generates two random primes and checks coprimality
const std::tuple<mpz_class, mpz_class> RsaKeys::generate_keys() const {
  dgrandprime p(bits_);
  dgrandprime q(bits_);

  return std::make_tuple(p.get_mpz_class(), q.get_mpz_class());
}
mpz_class RsaKeys::calculate_d(mpz_class totient, mpz_class e) {
  // we want the second value: y
  mpz_class d = extended_euclidean(totient, e)[1];
  // make sure d is in our bounds

  mpz_class bounded_d = d % totient;
  // -- Function: void mpz_mod (mpz_t R, const mpz_t N, const mpz_t D)

  // C++ mod arithmetic not suitable if d is negative
  // http://stackoverflow.com/a/12089637
  if (bounded_d < 0) {
    bounded_d = bounded_d + totient;
  }

  return bounded_d;
}
std::vector<mpz_class> RsaKeys::extended_euclidean(mpz_class a, mpz_class b) {
  std::vector<mpz_class> x_y_gcd(3);

  mpz_class x, last_x, y, last_y, r, last_r;
  x = last_y = 0;
  y = last_x = 1;
  r = b;
  last_r = a;
  while (r != 0) {
    mpz_class q = last_r / r;  // floor division because of int type
    // mpz_class r = b % a;
    mpz_class tmp = r;
    r = last_r - q * tmp;
    last_r = tmp;

    tmp = x;
    x = last_x - q * tmp;
    last_x = tmp;

    tmp = y;
    y = last_y - q * tmp;
    last_y = tmp;
  }
  x_y_gcd = {last_x, last_y, last_r};
  return x_y_gcd;
}
// helper function to get gcd
const mpz_class RsaKeys::get_gcd(mpz_class p, mpz_class q) const {
  mpz_class gcd = 1;
  for (mpz_class i = 1; ((i <= p) && (i <= q)); ++i) {
    if ((p % i == 0) && (q % i == 0)) {
      gcd = i;
    }
  }

  return gcd;
}

// helper function to check for primality
inline bool RsaKeys::is_coprime(mpz_class p, mpz_class q) const {
  return (get_gcd(p, q) != 1) ? false : true;
}



unsigned int RsaKeys::compute_e(mpz_class totient) {
  // why not use dgrandominteger...this is what it's for
  dgrandprime e(bits_);
  if (bits_ > 17) {
    return 65537;
  } else {
    for (int i = 0; i < 9; ++i) {
      if (is_coprime(e.get_mpz_class(), totient)) {
        return mpz_get_ui(e.get_mpz_class().get_mpz_t());
      } else {
        e.reroll();
      }
    }
  }
  std::cerr << "no coprime values";
  return 0;
}

