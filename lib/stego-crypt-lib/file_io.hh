#pragma once

#include <string>


enum class File_type {
  BMP,
  WAV,
  UNKNOWN
};

// loads entire file contents into the return string
std::string message_from_file(const std::string& fname);
// saves msg out to the file
void message_to_file(const std::string& msg, const std::string& fname);
File_type file_type_of(const std::string& fname);
