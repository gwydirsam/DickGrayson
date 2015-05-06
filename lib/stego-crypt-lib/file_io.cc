#include <fstream>
#include <sstream>
#include <algorithm>
#include "file_io.hh"

std::string message_from_file(const std::string& fname) {std::string msg;
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
