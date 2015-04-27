#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <unistd.h>
#include <getopt.h>

#include <rsa-attack-lib/common_modulus.hh> // comodulus namespace
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
  std::cerr << "Usage is --attack [type] --filename [filename] (--filename2 [filename])" << std::endl;
}

bool is_everything_correct(int file_count, int aflag, bool ioerror) {
  if (ioerror) {
    std::cerr
        << "File i/o error. Check that file exists and has correct permissions."
        << std::endl;
  }
  if (aflag == -1) {
    std::cerr << "missing argument --attack [type]" << std::endl;
    what_attack_types();
  }
  if(aflag == 1 && file_count < 2){
    std::cerr << "needs two filenames for the " << attack_types[aflag] << "attack" << std::endl;
  }
  else if (file_count == 0) {
    std::cerr << "missing argument --filename [file_to_crack]" << std::endl;
  }
}

int main(int argc, char* argv[]) {
  /* options descriptor */
  static struct option longopts[] = {{"attack", required_argument, NULL, 'a'},
                                     {"filename", required_argument, NULL, 'f'},
                                     {"filename2", required_argument, NULL, 'g'},
                                     {"help", no_argument, NULL, 'h'},
                                     {NULL, 0, NULL, 0}};

  bool ioerror = false;
  int option_index = 0;
  int file_count = 0, aflag = -1, ch = 0;
  std::fstream f_1;
  std::fstream f_2;
  while ((ch = getopt_long(argc, argv, "a:f:g:h", longopts, &option_index)) !=
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
    case 'f': {
      file_count += 1;
      std::string fname = std::string(optarg);
      f_1.open(fname, std::ios::in);
      if (!f_1.is_open()) {
        ioerror = true;
      } else {
        //std::string line = "";
        // this should pass to our fctn eventually
        // for now, test it's reading the right file
        //while (std::getline(f, line)) {
        //<< line << '\n';
        //}
      }

      break;
    }
    case'g': {
      file_count += 1;

      std::string fname = std::string(optarg);
      f_2.open(fname, std::ios::in);
      if (!f_2.is_open()) {
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
    rsatk::RSA_data r_1 = rsatk::parse_rsa_file(f_1);
    if(aflag == 0) {
      factoratk::factorization_attack(r_1);
    }
    else if (aflag == 1) {
      rsatk::RSA_data r_2 = rsatk::parse_rsa_file(f_2);
      comodulus::common_modulus_attack(r_1, r_2);
    }
    else if (aflag == 2) {
      //we'll just see if this exists... -___-
    }
  }

  argc -= optind;
  argv += optind;


  std::exit(EXIT_SUCCESS);
}
