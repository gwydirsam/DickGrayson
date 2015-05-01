#pragma once

#include <string>

// args

struct Arguments {
  bool verbose = false;
  bool extract = false; // if false, we embed
  std::string input_fname;
  std::string output_fname;
  std::string message_fname;
};

enum class Error_code {
  UNKNOWN_ARG,
  UNKNOWN_TYPE,
  UNSPECIFIED_TYPE,
  MISSING_ARG,
  MISSING_INPUT,
  MISSING_OUTPUT,
  INACCESSIBLE_FILE,
  HELP_ARG,
  SUCCESS
};

// Reads command line arguments and stores them in args
Error_code read_args(int argc, char* argv[], Arguments* args);
void process_error_code(Error_code err_code);

void print_help();
void print_usage(bool help = false);
// prints str to stdout if condition is true
void print_if(std::string str, bool condition);
