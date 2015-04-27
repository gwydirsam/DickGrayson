#pragma once
#define DEFINING_EXCEPTIONS

#include "exception_util.hh"

namespace DG {
namespace Type {

//// Custom dgtype exceptions go here

// throw the Invalid_format exception like this:
//
//     throw DG::Type::Invalid_format("BMP")
//
// result will be:
//
//     "BMP: Invalid_format_exception"
//
// type is Invalid_format_exception

DEFINE_DGTYPE_EXCEPT(Invalid_format)
DEFINE_DGTYPE_EXCEPT(Inaccessible_file)

}
}

#undef DEFINE_DGTYPE_EXCEPT
#undef DEFINING_EXCEPTIONS
