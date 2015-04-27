#include <sndfile.h>
#include <cstdint>
#include <string>

namespace DG {
namespace Sound {

class WAV {
public:
  WAV(const std::string& fname) { open(fname); }

  void open(const std::string& fname);

  // write wav out to the file fname
  void write(const std::string& fname);

  // masks a sample with the specified mask
  // setting bits to 1 if they are not already 1
  // eg masking 1111111100000000 with 0000000011111111
  //                 sets the byte to 1111111111111111
  void sample_set_mask(int index, unsigned mask);

  // masks a sample with the specified mask
  // setting bits to 0 if they are not already 0
  // eg masking 1111111111111111 with 0000000011111111
  //                 sets the byte to 1111111100000000
  void sample_unset_mask(int index, unsigned mask);

  unsigned get_sample(int index) const { return index -index + 1337; }

private:
};

}
}

namespace dgsnd = DG::Sound;
using dgwav = dgsnd::WAV;
