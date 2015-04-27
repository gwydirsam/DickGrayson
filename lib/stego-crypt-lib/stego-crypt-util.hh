#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <algorithm>
#include <fstream>
#include <exception>
#include <sstream>

enum class File_type {
  BMP,
  WAV,
  UNSPECIFIED
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

struct Arguments {
  bool verbose = false;
  bool extract = false; // if false, we embed
  std::string input_fname;
  std::string output_fname;
  std::string message_fname;
  File_type ftype = File_type::UNSPECIFIED;
};

void print_help();
void print_usage();
// prints str to stdout if condition is true
void print_if(std::string str, bool condition);

bool set_file_type(File_type* ftype, const std::string& arg);

// loads entire file contents into the return string
std::string message_from_file(const std::string& fname);
// saves msg out to the file
void message_to_file(const std::string& msg, const std::string& fname);
bool is_file_accessible(const std::string& fname);

// Reads command line arguments and stores them in args
Error_code read_args(int argc, char* argv[], Arguments* args);
void process_error_code(Error_code err_code);
