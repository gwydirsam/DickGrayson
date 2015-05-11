#include <iostream>
#include "rsa-crypt-lib/rsa-crypt-lib.hh"

#include <gmpxx.h>

int main(int argc, char *argv[]) {
  std::cout << "CSCE315 Project 4" << std::endl;
  int bits;
  std::string message;
  std::cout<<"What size bit numbers do you want to generate?"<<std::endl;
  std::cin>>bits;
 
  std::cout<<"What message do you want to encode?"<<std::endl;
  std::cin<<message;
  RsaKeys my_keys(bits, message);
  
  return 0;
}
