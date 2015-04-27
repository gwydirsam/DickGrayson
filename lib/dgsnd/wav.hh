#include <sndfile.h>
#include <string>

namespace DG {
namespace Sound {

class WAV {
public:
  WAV(const std::string& fname) { open(fname); }

  void open(const std::string& fname);

  // write wav out to the file fname
  void write(const std::string& fname);
private:
};

}
}
