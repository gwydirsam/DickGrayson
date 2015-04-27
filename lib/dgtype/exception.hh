#pragma once

#include <exception>
#include <string>

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

//
////
//////////
/////////////
//// Custom Exceptions Below Here

// throw like this:
//     throw DG::Type::Invalid_format("BMP")
// result will be "BMP: Invalid_format_exception"
// type is Invalid_format_exception
DEFINE_DGTYPE_EXCEPT(Invalid_format);
DEFINE_DGTYPE_EXCEPT(Inaccessible_file);

}
}

#undef DEFINE_DGTYPE_EXCEPT
