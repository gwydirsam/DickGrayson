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


const std::vector<std::string> attack_types = {"factoring", "common_modulus", "other"};

void what_attack_types() {
  std::cerr << "\nType can be ";
  for (std::size_t i = 0; i < attack_types.size(); ++i) {
    std::cerr << "\'" << attack_types[i] << "\', ";
  }
  std::cerr << std::endl;
}

void usage() {
  std::cerr << "Usage is --attack [type] --pubkey1 [filename] (--pubkey2 [filename] --pubkey3 [filename] --ciphertext [filename])" << std::endl;
}

bool is_everything_correct(int file_count, int aflag, bool ioerror) {
  if (ioerror) {
    std::cerr
        << "File i/o error. Check that file exists and has correct permissions."
        << std::endl;
    return false;
  }
  if (aflag == -1) {
    std::cerr << "missing argument --attack [type]" << std::endl;
    what_attack_types();
    return false;
  }
  if(aflag == 1 && file_count < 2){
    std::cerr << "needs two filenames for the " << attack_types[aflag] << "attack" << std::endl;
    return false;
  }
  if(aflag == 2 && file_count < 4){
    std::cerr << "needs three public keys, and one ciphertext";
  }
  else if (file_count == 0) {
    std::cerr << "missing argument --pubkey1 [file_to_crack]" << std::endl;
    return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  /* options descriptor */
  static struct option longopts[] = {{"attack", required_argument, NULL, 'a'},
                                     {"ciphertext", required_argument, NULL, 'b'},
                                     {"ciphertext2", required_argument, NULL, 'c'},
                                     {"pubkey1", required_argument, NULL, 'x'},
                                     {"pubkey2", required_argument, NULL, 'y'},
                                     {"pubkey3", required_argument, NULL, 'z'},
                                     {"help", no_argument, NULL, 'h'},
                                     {NULL, 0, NULL, 0}};

  bool ioerror = false;
  int option_index = 0;
  int file_count = 0, aflag = -1, ch = 0;
  std::fstream f_1;
  std::fstream f_2;
  std::fstream f_3;
  std::fstream cipher_file, cipher_file2;
  while ((ch = getopt_long(argc, argv, "a:b:c:x:y:z:h", longopts, &option_index)) !=
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
    case 'x': {
      file_count += 1;
      std::string fname = std::string(optarg);
      f_1.open(fname, std::ios::in);
      if (!f_1.is_open()) {
        ioerror = true;
        std::cout << fname << " : error." << std::endl;
      }

      break;
    }
    case 'y': {
      file_count += 1;

      std::string fname = std::string(optarg);
      f_2.open(fname, std::ios::in);
      if (!f_2.is_open()) {
        ioerror = true;
        std::cout << fname << " : error." << std::endl;
      }
      break;
    }
    case 'z': {
      file_count += 1;

      std::string fname = std::string(optarg);
      f_3.open(fname, std::ios::in);
      if (!f_3.is_open()) {
        ioerror = true;
        std::cout << fname << " : error." << std::endl;
      }
      break;
    }
    case 'b': {
      file_count += 1;

      std::string fname = std::string(optarg);
      cipher_file.open(fname, std::ios::in);
      if (!cipher_file.is_open()) {
        ioerror = true;
        std::cout << fname << " : error." << std::endl;
      }
      break;
    }
    case 'c': {
      file_count += 1;

      std::string fname = std::string(optarg);
      cipher_file2.open(fname, std::ios::in);
      if (!cipher_file2.is_open()) {
        std::cout << fname << " : error." << std::endl;
        ioerror = true;
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
  }

  bool good = is_everything_correct(file_count, aflag, ioerror);

  if(good){
    std::cout << "Starting decryption..." << std::endl;
    rsatk::RSA_data r_1 = rsatk::parse_rsa_file(f_1);
    if(aflag == 0) {
      factoratk::factorization_attack(r_1);
    }
    else if (aflag == 1) {
      rsatk::RSA_data r_2 = rsatk::parse_rsa_file(f_2);
      r_1.C = base64_decode(rsatk::read_cipher_text(cipher_file));
      r_2.C = base64_decode(rsatk::read_cipher_text(cipher_file2));

      comodulus::common_modulus_attack(r_1, r_2);
    }
    else if (aflag == 2) {
      rsatk::RSA_data r_2 = rsatk::parse_rsa_file(f_2);
      rsatk::RSA_data r_3 = rsatk::parse_rsa_file(f_3);
      std::string c = base64_decode(rsatk::read_cipher_text(cipher_file));
      r_1.C = r_2.C = r_3.C = c;
      lowexp::low_exponent_attack(r_1, r_2, r_3);
    }
  }

  argc -= optind;
  argv += optind;


  std::exit(EXIT_SUCCESS);
}
