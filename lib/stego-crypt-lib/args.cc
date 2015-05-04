#include <unistd.h>
#include <getopt.h>
#include <dgtype/dgtype.hh>
#include "args.hh"
#include "file_io.hh"

Error_code read_args(int argc, char* argv[], Arguments* args) {int c;

  while (true) {
    static struct option long_options[] =
    {
      {"verbose", no_argument, NULL, 'v'},
      {"help", no_argument, NULL, 'h'},
      {"extract", no_argument, NULL, 'e'}, {"input", required_argument, NULL, 'i'},
      {"output", required_argument, NULL, 'o'},
      {"file", required_argument, NULL, 'f'},
      {0, 0, 0, 0}
    };

    int option_index = 0;
    c = getopt_long (argc, argv, "evhi:o:f:",
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
              << "but the location to save the message when extracting)\n";
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


void print_help() {
  print_usage(true);
  std::cout << "-- Munchkinsteg help\n\n"
               "Munchkinsteg is a BMP and WAV file steganography utility.\n"
               "It can embed message files into music and image files as well as\n"
               "extract messages that may be embedded in a music or image file and\n"
               "store that message in a file.\n";
  std::cout << std::endl;
  std::cout << "Media types supported:\n  - Windows BMP\n  - PCM 16-bit WAV\n";
  std::cout << std::endl
            << "Long       short  desc\n"
               "--extract  -e     extract a message instead of embedding\n"
               "--help     -h     show this screen\n"
               "--input    -i     location of input bmp/wav file to embed in or extract from\n"
               "--file     -f     location of file containing the message to embed\n"
               "--output   -o     location to output stego file or extract message file\n"
               "--verbose  -v     verbosely describe stego process\n\n";
}

void print_usage(bool help) {
  std::cout << "usage: munchkinsteg [-i <wav|bmp file> -o <wav|bmp file> -f <message file>]\n"
               "               ~OR~ [-e -i <wav|bmp file> -o <message file>]\n\n";
  if (!help) {
    std::cout << "NOTE: The supported media types are:\n  - Windows BMP\n  - PCM 16-bit WAV\n";
  }
}

void print_if(std::string str, bool condition) {
  if (condition) {
    std::cout << str;
  }
}
