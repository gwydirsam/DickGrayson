#include <iostream>
#include "rsa-crypt-lib/rsa-crypt-lib.hh"

#include <gmpxx.h>

int main(int argc, char *argv[]) {
  std::cout << "CSCE315 Project 4" << std::endl;
  int bits;
  std::cout<<"What size bit numbers do you want to generate?"<<std::endl;
  std::cin>>bits;
 
  RsaKeys my_keys(bits);
  
  return 0;
}
