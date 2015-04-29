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

// Some libraries declare some functions const, this allows us to use
// those functions even on const objects
#define CONST_FUNC(obj, func) const_cast<decltype(obj)*>(&obj)->func
#define CONST_CALL(obj, func) CONST_FUNC(obj, func)()
#define CONST_CALL_1(obj, func, arg) CONST_FUNC(obj, func)(arg) // pass arg to func
