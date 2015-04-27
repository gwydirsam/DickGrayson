#pragma once
// only files who ABSOLUTELY need this header
// can include it!
#ifdef __DEFINING_EXCEPTIONS

#include <exception>
#include <string>

//// Macro for easily defining dgtype exceptions

#define DEFINE_DGTYPE_EXCEPT(shortname) \
    typedef struct shortname ## _exception : public Exception { \
        shortname ## _exception(std::string qualifier) \
        : Exception(qualifier) { name = #shortname "_exception"; } \
    } shortname;

namespace DG {
namespace Type {

//// Base exception class

struct Exception : public std::exception {
  Exception() {}
  Exception(std::string qualifier) : qualifier(qualifier) {}
  virtual const char* what() const throw() {
    std::string str = qualifier + ": " + name;
    return str.c_str();
  }
protected:
  std::string qualifier = "Error";
  std::string name = "Un-named exception";
};

}
}

#endif
