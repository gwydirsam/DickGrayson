#include <sndfile.h>
#include <string>

namespace DG {
namespace Sound {

class WAV {
public:
  struct Invalid_format_exception : public std::exception {

  WAV(const std::string& fname) { open(fname); }

  void open(const std::string& fname);

  // write wav out to the file fname
  void write(const std::string& fname);
private:
};

}
}
