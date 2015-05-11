#include <iostream>
#include <getopt.h>
#include <fstream>
#include "rsa-crypt-lib/rsa-crypt-lib.hh"

#include <gmpxx.h>

int main(int argc, char *argv[]) {
  std::cout << "CSCE315 Project 4" << std::endl;
  /*int bits;
  std::string message;

  std::cout<<"What size bit numbers do you want to generate the RSA Key with? (up to 1024)"<<std::endl;
  std::cin>>bits;

  
  std::cout<<"What message do you want to encode?"<<std::endl;
  std::cin>>message;

  std::string mess = "Hello world my name is rafa";
  RsaKeys r1(bits);
  */
 
  RsaKeys r1(512);
  int opt;

  std::string message;

  while((opt = getopt(argc, argv, "i:")) != -1) {
    switch(opt) {
      case 'i' : 
        message = std::string(optarg); 
       

        break;
      
      /*case 'o' :
        std::string output_file_path = std::string(optarg);
        of2.open(output_file_path); 
        if(!of2.is_open()){
          std::cout<<output_file_path<< " : error"<<std::endl;
        } 
        break;*/
    } 
  }  
  
  std::string encrypted_message = r1.encrypt_message(message); 
  std::cout<<"Encrypted Message : "<<encrypted_message<<std::endl;

  std::string decrypted_message = r1.decrypt_message(encrypted_message);
  std::cout<<"Decrypted Message : "<<decrypted_message<<std::endl;
  
}
