#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <unistd.h>
#include <getopt.h>

#include <rsa-attack-lib/rsa-attack-lib.hh>

const std::vector<std::string> attack_types = {"factoring", "chinese_rt",
                                               "other"};

void what_attack_types() {
  std::cout << "\nType can be ";
  for (std::size_t i = 0; i < attack_types.size(); ++i) {
    std::cout << "\'" << attack_types[i] << "\', ";
  }
  std::cout << std::endl;
}

void usage() {
  std::cout << "Usage is --attack [type] --filename [filename]" << std::endl;
  what_attack_types();
}

void what_went_wrong(int flag, bool ioerror) {
  if (ioerror) {
    std::cout
        << "File i/o error. Check that file exists and has correct permissions."
        << std::endl;
  }
  if (flag == 1) {
    std::cout << "missing argument --attack [type]" << std::endl;
    what_attack_types();
  } else if (flag == 2) {
    std::cout << "missing argument --filename [file_to_crack]" << std::endl;
  }
}

int main(int argc, char* argv[]) {
  /* options descriptor */
  static struct option longopts[] = {{"attack", required_argument, NULL, 'a'},
                                     {"filename", required_argument, NULL, 'f'},
                                     {"help", no_argument, NULL, 'h'},
                                     {NULL, 0, NULL, 0}};

  bool ioerror = false;
  int option_index = 0;
  int fflag = 0, aflag = 0, ch = 0;
  while ((ch = getopt_long(argc, argv, "a:f:h", longopts, &option_index)) !=
         -1) {
    switch (ch) {
      case 'a': {
        aflag = 1;
        if (optarg == attack_types[0]) {
          std::cerr << "Running " << attack_types[0] << " on file.."
                    << std::endl;
        }
        break;
      }
      case 'f': {
        fflag = 2;
        std::string fname = std::string(optarg);
        std::fstream f(fname, std::ios::in);
        if (!f.is_open()) {
          ioerror = true;
        } else {
          std::string line = "";
          // this should pass to our fctn eventually
          // for now, test it's reading the right file
          while (std::getline(f, line)) {
            std::cout << line << '\n';
          }
        }

        break;
      }
      case 'h':
      case '?':
      default: {
        usage();
        std::exit(EXIT_FAILURE);
      }
    }
  }

  if (!fflag || !aflag) {
    usage();
  }

  argc -= optind;
  argv += optind;

  what_went_wrong(fflag + aflag, ioerror);

  std::exit(EXIT_SUCCESS);
}
