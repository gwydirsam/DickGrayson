#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <algorithm>
#include <dgtype/dgtype.hh>

enum class File_type {
  BMP,
  WAV,
  UNSPECIFIED
};

enum class Error_code {
  UNKNOWN_ARG,
  UNKNOWN_TYPE,
  MISSING_ARG,
  HELP_ARG,
  SUCCESS
};

struct Arguments {
  bool verbose;
  std::string input_fname;
  std::string output_fname;
  std::string message_fname;
  File_type ftype = File_type::UNSPECIFIED;
};

void print_help();
void print_usage();
bool set_file_type(File_type* ftype, const std::string& arg);

// Reads command line arguments and stores them in args
Error_code read_args(int argc, char* argv[], Arguments* args);

void process_error_code(Error_code err_code);
