#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <unistd.h>
#include <getopt.h>

#include <rsa-attack-lib/common_modulus.hh> // comodulus namespace
#include <rsa-attack-lib/low_exponent.hh> // lowexp namespace
#include <rsa-attack-lib/factorization_attack.hh> // factoratk namespace
#include <rsa-attack-lib/rsa-attack-lib.hh> // rsatk namespace


const std::vector<std::string> attack_types = {"factoring", "common_modulus", "low_exponent"};

bool is_whole_number(std::string s)
{
  for(int i = 0; i < s.size(); ++i){
    if(!(int(s[i]) >= 48 && (int)s[i] <= 57)){
      return false;
    }
  }
  return true;
}

mpz_class get_whole_number(){
  int attempts = 0;
  mpz_class n = 0;
  std::string n_str = "";
  while(attempts < 5){
    std::cout << "(Please enter a whole number):\n";
    try {
      std::cin >> n_str;

      if (!is_whole_number(n_str) || std::cin.fail()){
        throw "Sorry, I don't think that's a whole number?\n";
      }
      if (n < 0){
        throw "Sorry, no negative numbers. Try something else? \n";
      }
      //std::cin.clear();
      n = mpz_class(n_str);
      return n;
    }
    catch (const char* error) {
      std::cout << error;
      attempts++;
    }
  }
  return -1;
}

void run_factoring(){
  rsatk::RSA_data r_1;

  std::cout << "What is the n value? \n";
  r_1.n = get_whole_number();
  std::cout << "What is the e value? \n";
  r_1.e = get_whole_number();
  std::cout << "Starting decryption..." << r_1.n << r_1.e;
  factoratk::factorization_attack(r_1);
}


void run_comodulus(){
  rsatk::RSA_data r_1;
  rsatk::RSA_data r_2;

  std::cout << "What is the common n value? \n";
  r_1.n  = r_2.n = get_whole_number();

  std::cout << "What is the first message's e value? ";
  r_1.e = get_whole_number();
  std::cout << "What is the second message's e value? ";
  r_2.e = get_whole_number();
  std::cout << "Provide the first encrypted message:\n";
  std::cin >> r_1.C;
  std::cout << "Provide the second encrypted message:\n";
  std::cin >> r_2.C;
  std::cout << "Starting decryption...";
  comodulus::common_modulus_attack(r_1, r_2);
}

void run_low_exp(){
  rsatk::RSA_data r_1;
  rsatk::RSA_data r_2;
  rsatk::RSA_data r_3;

  std::cout << "What is the common e value? ";
  r_1.e = r_2.e = r_3.e = get_whole_number();
  std::cout << "What is the first n value? ";
  r_1.n = get_whole_number();
  std::cout << "What is the second n value? ";
  r_2.n = get_whole_number();
  std::cout << "What is the third n value? ";
  r_3.n = get_whole_number();
  std::cout << "Provide the first encrypted message:  \n";
  std::cin >> r_1.C;
  std::cout << "Provide the second encrypted message:  \n";
  std::cin >> r_2.C;
  std::cout << "Provide the third encrypted message:  \n";
  std::cin >> r_3.C;
  std::cout << "Starting decryption...";
  lowexp::low_exponent_attack(r_1, r_2, r_3);
}


void what_attack_types() {
  std::cerr << "\nType can be ";
  for (std::size_t i = 0; i < attack_types.size(); ++i) {
    std::cerr << "\'" << attack_types[i] << "\', ";
  }
  std::cerr << std::endl;
}

void usage() {
  std::cerr << "Usage is --attack [type] " << std::endl;
}


int main(int argc, char* argv[]) {
  /* options descriptor */
  static struct option longopts[] = {{"attack", required_argument, NULL, 'a'},
                                     {"help", no_argument, NULL, 'h'},
                                     {NULL, 0, NULL, 0}};

  bool ioerror = false;
  int option_index = 0;
  int file_count = 0, aflag = -1, ch = 0;
  while ((ch = getopt_long(argc, argv, "a:h", longopts, &option_index)) !=
         -1) {
    switch (ch) {
    case 'a': {
      for(size_t i = 0; i < attack_types.size(); ++i){
        if(attack_types[i] == optarg) {
          aflag = i;
        }
      }
      if(aflag == -1) {
        what_attack_types();
      }
      break;
    }
    case 'h':
      break;
    case '?':
      break;
    default: {
      usage();
      what_attack_types();
      std::exit(EXIT_FAILURE);
    }
    }
    argc -= optind;
    argv += optind;

  }
  if(aflag == -1){
    usage();
    what_attack_types();
    std::exit(EXIT_FAILURE);
  }

  if(aflag == 0) {
    run_factoring();
  }
  if(aflag == 1) {
    run_comodulus();
  }
  if(aflag == 2) {
    run_low_exp();
  }

  std::exit(EXIT_SUCCESS);
}

//rsatk::RSA_data r_1 = rsatk::parse_rsa_file(f_1);
//else if (aflag == 1) {
//rsatk::RSA_data r_2 = rsatk::parse_rsa_file(f_2);
//r_1.C = base64_decode(rsatk::read_cipher_text(cipher_file));
//r_2.C = base64_decode(rsatk::read_cipher_text(cipher_file2));
//
//comodulus::common_modulus_attack(r_1, r_2);
//}
//else if (aflag == 2) {
//rsatk::RSA_data r_2 = rsatk::parse_rsa_file(f_2);
//rsatk::RSA_data r_3 = rsatk::parse_rsa_file(f_3);
//std::string c = base64_decode(rsatk::read_cipher_text(cipher_file));
//r_1.C = r_2.C = r_3.C = c;
//lowexp::low_exponent_attack(r_1, r_2, r_3);
//}
//}
