#include "stego-crypt-util.hh"
#include <dgimg/dgimg.hh>

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

std::string message_from_file(const std::string& fname) {
  std::string msg;
  std::ifstream ifs(fname);
  std::ostringstream oss;
  oss << ifs.rdbuf();
  msg = oss.str();
  return msg;
}

void message_to_file(const std::string& msg, const std::string& fname) {
  std::ofstream ofs(fname);
  ofs << msg;
}

void print_psnr(const std::string& fname_a, const std::string& fname_b) {
  dgbmp bmp_a(fname_a);
  dgbmp bmp_b(fname_b);
  double psnr = bmp_a.peak_signal_noise_ratio(bmp_b);
  std::cout << "Peak signal to noise ratio: " << psnr << std::endl;
}

bool is_file_accessible(const std::string& fname) {
  std::ifstream ifs(fname);
  if (ifs.good()) {
    return true;
  }
  return false;
}

void print_help() {
  print_usage();
  std::cout << std::endl
            << "Long         short  desc\n"
            << "--extract    -e     extract a message instead of embedding\n"
            << "--help       -h     show this screen\n"
            << "--input      -i     location of input file to embed/extract message in\n"
            << "--message    -m     location of file containing the message to embed\n"
            << "--output     -o     location of output stego file or extracted message file\n"
            << "--type       -t     indicate type of media (wav or bmp)\n"
            << "--verbose    -v     verbosely describe steg process\n\n";
}

void print_usage() {
  std::cout << "usage: munchkinsteg [-ehv] [-i inputfile]\n"
            << "                    [-m messagefile] [-o outputfile] [-t wav | bmp]\n";
}

Error_code read_args(int argc, char* argv[], Arguments* args) {
  int c;

  while (true) {
    static struct option long_options[] =
    {
      {"verbose", no_argument, NULL, 'v'},
      {"help", no_argument, NULL, 'h'},
      {"extract", no_argument, NULL, 'e'},
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
    case 'e':
      args->extract = true;
      break;
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
  if (args->ftype == File_type::UNSPECIFIED) {
    return Error_code::UNSPECIFIED_TYPE;
  }
  if (args->input_fname.empty()) {
    return Error_code::MISSING_INPUT;
  }
  if (args->output_fname.empty()) {
    return Error_code::MISSING_OUTPUT;
  }
  if (!is_file_accessible(args->input_fname) ||
     (!args->extract && !is_file_accessible(args->message_fname))) {
    return Error_code::INACCESSIBLE_FILE;
  }
  return Error_code::SUCCESS;
}

void process_error_code(Error_code err_code) {
  switch (err_code) {
  case Error_code::UNSPECIFIED_TYPE:
    std::cerr << "error: unspecified type.\n";
    break;
  case Error_code::MISSING_INPUT:
    std::cerr << "error: must specify an input file.\n";
    break;
  case Error_code::MISSING_OUTPUT:
    std::cerr << "error: must specify an output file.\n"
              << "(Note the output is a media file when embedding, "
              << "but a file containing a message when extracting)\n";
    break;
  case Error_code::INACCESSIBLE_FILE:
    std::cerr << "error: could not open file for reading.\n";
    break;
  case Error_code::HELP_ARG:
    exit(EXIT_SUCCESS);
  case Error_code::SUCCESS:
    return;
  }
  print_usage();
  exit(EXIT_FAILURE);
}
