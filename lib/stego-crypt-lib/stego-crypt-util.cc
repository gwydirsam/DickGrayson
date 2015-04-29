#include <dgtype/dgtype.hh>
#include <algorithm>
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

std::string message_from_file(const std::string& fname) {std::string msg;
  std::ifstream ifs(fname);
  std::ostringstream oss;
  oss << ifs.rdbuf();
  msg = oss.str();
  return msg;
} void message_to_file(const std::string& msg, const std::string& fname) {
  std::ofstream ofs(fname);
  ofs << msg;
}

void print_help() {
  print_usage(true);
  std::cout << "Media types supported:\n  - Windows BMP\n  - PCM 16-bit WAV\n";
  std::cout << std::endl
            << "Long       short  desc\n"
            << "--extract  -e     extract a message instead of embedding\n"
            << "--help     -h     show this screen\n"
            << "--input    -i     location of input bmp/wav file to embed in or extract from\n"
            << "--message  -m     location of file containing the message to embed\n"
            << "--output   -o     location of output stego file or extracted message file\n"
            << "--verbose  -v     verbosely describe stego process\n\n";
}

void print_usage(bool help) {
  std::cout << "usage: munchkinsteg [hv] [-i <wav|bmp file> -o <wav|bmp file> -m <message file>]\n"
            << "                    ~OR~ [-e -i <wav|bmp file> -o <message file>]\n\n";
  if (!help) {
    std::cout << "NOTE: The supported media types are:\n  - Windows BMP\n  - PCM 16-bit WAV\n";
  }
}

void print_if(std::string str, bool condition) {
  if (condition) {
    std::cout << str;
  }
}

File_type file_type_of(const std::string& fname) {
  int extension_pos = fname.find_last_of('.');
  if (extension_pos != -1) {
    std::string extension = fname.substr(extension_pos + 1);
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    if (extension == "wav") {
      return File_type::WAV;
    } else if (extension == "bmp") {
      return File_type::BMP;
    }
  }
  return File_type::UNKNOWN;
}

std::unique_ptr<Abstract_embedding_agent> which_embedding_agent(File_type type, std::string inmedia_fname,
                                                                std::string outmedia_fname) {
  std::unique_ptr<Abstract_embedding_agent> embedder;

  if (type == File_type::BMP) {
    embedder =
      std::make_unique<BMP_embedding_agent>(inmedia_fname, outmedia_fname);
  } else {
    embedder =
      std::make_unique<WAV_embedding_agent>(inmedia_fname, outmedia_fname);
  }
  return embedder;
}

std::unique_ptr<Abstract_extracting_agent> which_extracting_agent(File_type type, std::string inmedia_fname) {
  std::unique_ptr<Abstract_extracting_agent> extractor;

  if (type == File_type::BMP) {
    extractor = std::make_unique<BMP_extracting_agent>(inmedia_fname);
  } else {
    extractor = std::make_unique<WAV_extracting_agent>(inmedia_fname);
  }
  return extractor;
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
      {0, 0, 0, 0}
    };

    int option_index = 0;
    c = getopt_long (argc, argv, "evhi:o:m:",
                     long_options, &option_index);
    if (c == -1) {
      break;
    }

    switch (c) {
    case 'v':
      args->verbose = true;
      break;
    case 'h':
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
    case ':':
      return Error_code::MISSING_ARG;
    case '?':
      return Error_code::UNKNOWN_ARG;
    }
  }
  if (file_type_of(args->input_fname) == File_type::UNKNOWN ||
      (!args->extract && file_type_of(args->output_fname) == File_type::UNKNOWN)) {
    return Error_code::UNKNOWN_TYPE;
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
    print_help();
    exit(EXIT_SUCCESS);
  case Error_code::UNKNOWN_ARG:
  case Error_code::UNKNOWN_TYPE:
  case Error_code::MISSING_ARG:
    break;
  case Error_code::SUCCESS:
    return;
  }
  print_usage();
  exit(EXIT_FAILURE);
}
