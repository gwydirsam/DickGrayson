#include <iostream>
#include <getopt.h>
#include <fstream>
#include "rsa-crypt-lib/rsa-crypt-lib.hh"

#include <gmpxx.h>

int main(int argc, char *argv[]) {
  std::cout << "CSCE315 Project 4" << std::endl;
  int bits;
  std::string message;

  std::cout<<"What size bit numbers do you want to generate the RSA Key with? (up to 1024)"<<std::endl;
  std::cin>>bits;

  if(!isdigit(bits)){
    std::cout<<"Did not enter a valid number"
    return 0;
  } 
  
  std::cout<<"What message do you want to encode?"<<std::endl;
  std::cin>>message;

  RsaKeys r1(bits);
  std::string encrypted_message = r1.encrypt_message(message); 
  std::cout<<"Encrypted Message : "<<encrypted_message;

  std::string decrypted_message = r1.decrypt_message(encrypted_message);
  std::cout<<"Decrypted Message : "<<decrypted_message<<std::endl;

  

 /* int opt;
  ostream f1; 
  while((opt = getopt(argc, argv, "n:t:")) != -1) {
    switch(opt) {
      case 'n' : 
        std::string fname = std::string(optarg);
        f1.open(fname);
        if(!f1.is_open()){
          std::cout<<fname << " : error"<<std::endl;
        }
        break;
      
      case 't' :
        
    }

   
  }*/
}
