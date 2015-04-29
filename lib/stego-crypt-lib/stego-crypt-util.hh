#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <algorithm>
#include <fstream>
#include <exception>
#include <sstream>
#include "abstract_extracting_agent.hh"
#include "abstract_embedding_agent.hh"
#include "bmp_embedding_agent.hh"
#include "wav_embedding_agent.hh"
#include "bmp_extracting_agent.hh"
#include "wav_extracting_agent.hh"

enum class File_type {
  BMP,
  WAV,
  UNKNOWN
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
};

void print_help();
void print_usage(bool help = false);
// prints str to stdout if condition is true
void print_if(std::string str, bool condition);

bool set_file_type(File_type* ftype, const std::string& arg);

// loads entire file contents into the return string
std::string message_from_file(const std::string& fname);
// saves msg out to the file
void message_to_file(const std::string& msg, const std::string& fname);

// Reads command line arguments and stores them in args
Error_code read_args(int argc, char* argv[], Arguments* args);
void process_error_code(Error_code err_code);

File_type file_type_of(const std::string& fname);

std::unique_ptr<Abstract_embedding_agent> which_embedding_agent(File_type, std::string inmedia,
                                                                std::string outmedia);
std::unique_ptr<Abstract_extracting_agent> which_extracting_agent(File_type, std::string inmedia);
