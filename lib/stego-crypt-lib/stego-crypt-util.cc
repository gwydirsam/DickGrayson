#include "stego-crypt-util.hh"

bool set_file_type(File_type* ftype, const std::string& arg) {
  std::string lower_arg = std::move(arg);
  std::transform(lower_arg.begin(), lower_arg.end(), lower_arg.begin(),
                 ::tolower);
  if (lower_arg == "wav") {
    *ftype = File_type::WAV;
  } else if (lower_arg == "bmp") {
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

Error_code read_args(int argc, char* argv[], Arguments* args) {
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
      args->verbose = true;
      break;
    case 'h':
      print_help();
      return Error_code::HELP_ARG;
    case 'i':
      args->input_fname = optarg;
      break;
    case 'o':
      args->output_fname = optarg;
      break;
    case 'm':
      args->message_fname = optarg;
      break;
    case 't':
      if (!set_file_type(&args->ftype, optarg)) {
        return Error_code::UNKNOWN_TYPE;
      }
      break;
    case ':':
      print_usage();
      return Error_code::MISSING_ARG;
    case '?':
      print_usage();
      return Error_code::UNKNOWN_ARG;
    }
  }
  return Error_code::SUCCESS;
}

void process_error_code(Error_code err_code) {
  switch (err_code) {
  case Error_code::UNKNOWN_ARG:
    exit(EXIT_FAILURE); // getopt_long already displayed error message
    break;
  case Error_code::UNKNOWN_TYPE:
    exit(EXIT_FAILURE); // set_file_type already displayed error message
    break;
  case Error_code::MISSING_ARG:
    exit(EXIT_FAILURE); // getopt_long already displayed error message
    break;
  case Error_code::HELP_ARG:
    exit(EXIT_SUCCESS);
    break;
  case Error_code::SUCCESS:
    break;
  }
}
