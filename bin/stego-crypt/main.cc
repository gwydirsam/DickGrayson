#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <dgtype/dgtype.hh>

enum class File_type {
  BMP,
  WAV,
  UNSPECIFIED
};

void print_help();
void print_usage();
bool set_file_type(File_type* ftype, const std::string& arg);

int main(int argc, char *argv[]) {
  bool verbose = false;
  std::string input_fname;
  std::string output_fname;
  std::string message_fname;
  File_type ftype = File_type::UNSPECIFIED;

  int c;

  while (true) {
    static struct option long_options[] =
    {
      {"verbose", no_argument, NULL, 'v'},
      {"help", no_argument, NULL, 'h'},
      {"input", required_argument, NULL, 'i'},
      {"output", required_argument, NULL, 'o'},
      {"message", required_argument, NULL, 'm'},
      {"type", required_argument, NULL, 't'},
      {0, 0, 0, 0}
    };

    int option_index = 0;
    c = getopt_long (argc, argv, "vhi:o:m:t:",
                     long_options, &option_index);
    if (c == -1) {
      break;
    }

    switch (c) {
    case 'v':
      verbose = true;
      break;
    case 'h':
      print_help();
      return 0;
    case 'i':
      input_fname = optarg;
      break;
    case 'o':
      output_fname = optarg;
      break;
    case 'm':
      message_fname = optarg;
      break;
    case 't':
      if (!set_file_type(&ftype, optarg)) {
        return 1;
      }
      break;
    case ':':
      print_usage();
      return 1;
    case '?':
      print_usage();
      return 1;
    }
  }
  if (ftype == File_type::WAV) {
    std::cout << "WAV files not yet supported\n";
  }
  return 0;
}

bool set_file_type(File_type* ftype, const std::string& arg) {
  if (arg == "wav") {
    *ftype = File_type::WAV;
  } else if (arg == "bmp") {
    *ftype = File_type::BMP;
  } else {
    std::cerr << "Unknown type: " << arg << std::endl;
    return false;
  }
  return true;
}

void print_help() {
  print_usage();
  std::cout << std::endl
            << "Long         short  desc\n"
            << "--help       -h     show this screen\n"
            << "--input      -i     location of input file to embed message in\n"
            << "--message    -m     location of file containing the message\n"
            << "--output     -o     location of output stego file\n"
            << "--type       -t     indicate type of media (wav or bmp)\n"
            << "--verbose    -v     verbosely describe steg process\n";
}

void print_usage() {
  std::cout << "usage: munchkinsteg [-hv] [-i inputfile]\n"
            << "                    [-m messagefile] [-o outputfile] [-t wav | bmp]\n";
}
