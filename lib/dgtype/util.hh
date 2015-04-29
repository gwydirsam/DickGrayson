#pragma once

#include <fstream>
#include <string>

inline bool is_file_accessible(const std::string& fname) {
  std::ifstream ifs(fname);
  if (ifs.good()) {
    return true;
  }
  return false;
}
