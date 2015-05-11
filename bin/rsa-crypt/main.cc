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

  
  std::cout<<"What message do you want to encode?"<<std::endl;
  std::cin>>message;

  std::string mess = "Hello world my name is rafa";
  RsaKeys r1(bits);
  std::string encrypted_message = r1.encrypt_message(message); 
  std::cout<<"Encrypted Message : "<<encrypted_message<<std::endl;

  std::string decrypted_message = r1.decrypt_message(encrypted_message);
  std::cout<<"Decrypted Message : "<<decrypted_message<<std::endl;
 
 /* RsaKeys r1(512);
  int opt;
  std::ofstream of1; 
  std::ofstream of2;

  std::ifstream if1;
  std::ifstream if2;

  std::string message_file_path;
  std::string message;
  std::string encrypted_message;
  std::string decrypted_message;

  while((opt = getopt(argc, argv, "i:o:m:")) != -1) {
    switch(opt) {
      case 'i' : 
        message_file_path = std::string(optarg);
        of1.open(message_file_path);
        if(!of1.is_open()){
          std::cout<<message_file_path << " : error"<<std::endl;
        }
        break;
      
      case 'o' :
        std::string output_file_path = std::string(optarg);
        of2.open(output_file_path); 
        if(!of2.is_open()){
          std::cout<<output_file_path<< " : error"<<std::endl;
        } 
        break;
    } 
  }  
  
  if1.open(message_file_path);
  getline(if1, message);
  encrypted_message =  r1.encrypt_message(message); 
  if1.close();
  
  if(of2.is_open()){
    of2<<r1.decrypt_message(encrypted_message);
  } 
  */
}
