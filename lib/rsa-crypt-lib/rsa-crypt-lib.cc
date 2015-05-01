#include "rsa-crypt-lib.hh"

#include <gmpxx.h>

#include <vector>

#include <iostream>
#include <tuple>      // std::tuple
#include <algorithm>  // std::min

#include <dgcrypto/dgcrypto.hh>

// to use 'random' is there more specific header?
// I meant #include <random> for std::random_device
// #include <random>
// sam: don't need this if we use dgrandprime

// generates two random primes and checks coprimality
RsaKeys::RsaKeys(mp_bitcnt_t k) : bits_{k} {
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
  this->encode_ = encode("Hello", e(), n());
   //std::cout<<"result of my_pow : "<<my_pow(2,8)<<std::endl; 
  this-> decode_ = decode(encode_result(), d(), n()); 
  // private key
  // std::cerr<<"Public key is : "<<p<<q<<d_<<std::endl;
}

//encodes message
std::string RsaKeys::encode(std::string message, mpz_class e, mpz_class n) {
  std::string inter = "";
  mpz_class cipher;
  std::string result = "";
  if(message.length() > 20){
    
    int k = 0;
    int i = 0;
    while(i < message.length()){
      while(i < message.length() && k < 20){
        
        mpz_class temp = (int) message.at(i);
        inter = temp.get_str();
        i++;
        k++; 
      }
      mpz_class pTxt = mpz_class(inter);
     // cipher = my_pow(pTxt, e) % n;
      mpz_ui_pow_ui(cipher.get_mpz_t(), pTxt, e);
      result += cipher.get_str() + 'n';
      inter = "";
      k = 0;
    }
  std::cout<<"result is : "<<result<<std::endl;
  return result;
  } else{
    for( int i = 0; i < message.length(); ++i) {
      mpz_class temp = (int) message.at(i);
      inter += temp.get_str();
           
    }
    mpz_class pTxt = mpz_class(inter);
    std::cout<<"pTxt"<<pTxt<<std::endl;
    //cipher = my_pow(pTxt, e) %n;
    mpz_ui_pow_ui(cipher.get_mpz_t(), pTxt.get_mpz_t(), e.get_mpz_t()); 
    result = cipher.get_str();
 
    return result;
  }
 return "Error";
}
//pow didn't work so had to generate my own
mpz_class RsaKeys::my_pow(mpz_class base, mpz_class exp) {
  mpz_class result = 1;
    for(mpz_class i = 0; i < exp; ++i){
      result = result*base;
    }
 return result; 
}

std::string RsaKeys::decode(std::string cryptText, mpz_class d, mpz_class n){
  std::cout<<"D is : "<< d<<std::endl;
  std::cout<<"N is : "<<n<<std::endl;
  std::cout<<"message to be decoded : "<<cryptText<<std::endl;
  std::string base = cryptText;
  std::string part = "";
  std::vector<std::string> partition;
  mpz_class nCount = 0;
  for(int i = 0; i < base.length(); ++i){
    if(base.at(i) == 'n'){
      partition.push_back(part);
      nCount++;
      part = "";
    }
    else {
      part += base.at(i);
    }
  }
  if(nCount == 0) partition.push_back(part);
    
    std::string buffer = "";
    for(int i = 0; i < partition.size(); ++i){
      mpz_class cTxt = mpz_class(partition.at(i));
      std::cout<<"cTxt : "<< cTxt<<std::endl;
      mpz_class pTxt = my_pow(cTxt, d) % n;
      std::cout<<"pTxt : " <<pTxt<<std::endl;
      buffer += pTxt.get_str();
    }
 
  std::string buffer2 = "";
  std::string output = "";
 
  for(int i = 0; i < buffer.length(); ++i){
    buffer2 = "";
    if(buffer.at(i) == '1'){
      buffer2 += buffer.at(i); 
      i++;
      buffer2 += buffer.at(i);
      i++;
      buffer2 += buffer.at(i);
    }
    else {
      buffer2 += buffer.at(i);
      i++;
      buffer2 += buffer.at(i);
    }
    std::cout<<"Buffer 2 value : "<<buffer2<<std::endl;
   output += (char) stoi(buffer2);
  } 
  return output;
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



const mpz_class RsaKeys::compute_e(mpz_class totient) {
  // why not use dgrandominteger...this is what it's for
  dgrandprime e(bits_);
  if (bits_ > 17) {
    return 65537;
  } else {
    for (int i = 0; i < 9; ++i) {
      if (is_coprime(e.get_mpz_class(), totient)) {
        return e.get_mpz_class();
      } else {
        e.reroll();
      }
    }
  }
  std::cerr << "no coprime values";
  return 0;
}

