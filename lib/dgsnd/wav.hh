#include <sndfile.h>
#include <string>

namespace DG {
namespace Sound {

class WAV {
public:
  struct Invalid_format_exception : public std::exception {
    virtual const char* what() const throw() {
      return "WAV: Invalid_format_exception";
    }
  } invalid_format;

  struct Inaccessible_file_exception : public std::exception {
    virtual const char* what() const throw() {
      return "WAV: Inaccessible_file_exception";
    }
  } inaccessible_file;

  WAV(const std::string& fname) { open(fname); }

  void open(const std::string& fname);

  // write wav out to the file fname
  void write(const std::string& fname);
private:
};

}
}
