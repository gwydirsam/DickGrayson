#include "dgcrypto/dgrandomprime.hh"

#include "rsa-crypt-lib.hh"

//generates two random primes and checks coprimality
mpz_class RsaCrypt::generate_key(){
  RandomPrime* prime1;
  prime1->generate_prime(30);

  RandomPrime* prime2; 
  prime2->generate_prime(30);

  while(!is_coprime(prime1, prime2)){
  	prime2->generate_prime(30);
  }
  
  return prime1;

}

//helper function to check for primality
bool RsaCrypt::is_coprime(mpz_class value1, mpz_class value2){
  int gcd = 1;
  for(int i = 1; i<= value1 && i <= value2; i++){
    if(value1 % i == 0 && value2 %i == 0){
      gcd = i;
    }
  }
  if(gcd != 1){
    return false;
  } 
  
  return true;
}

mpz_class RsaCrypt::compute_n(mpz_class p, mpz_class q){
  return p*q;
}

mpz_class RsaCrypt::compute_theta_n(mpz_class p, mpz_class q){
  return (p-1)*(q-1);
}
