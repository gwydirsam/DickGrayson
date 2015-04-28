#include <sndfile.h>
#include <vector>
#include <cstdint>
#include <string>

namespace DG {
namespace Sound {

class WAV {
public:
  WAV(const std::string& fname) { open(fname); }
  ~WAV() { sf_close(data); }

  bool operator==(const WAV& other) const {
    return (this == &other ||
            samples == other.samples);
  }

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

  int get_sample(int index) const { return samples[index]; }

  unsigned get_num_samples() const { return samples.size(); }

private:
  std::vector<int> samples;
  SNDFILE* data;
  SF_INFO data_info;

  //// helper functions
  bool is_wav_format() const;
  // populates samples vector from the data
  void extract_samples();

  // returns the number of samples the data contains
  size_t calc_num_samples() const;
};

}
}

namespace dgsnd = DG::Sound;
using dgwav = dgsnd::WAV;
