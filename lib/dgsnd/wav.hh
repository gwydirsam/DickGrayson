#pragma once

#include <sndfile.h>
#include <vector>
#include <cstdint>
#include <string>

namespace DG {
namespace Sound {

class WAV {
public:
  WAV(const std::string& fname) { open(fname); }

  bool operator==(const WAV& other) const {
    return (this == &other ||
            samples == other.samples);
  }

  void open(const std::string& fname);

  // write wav out to the file fname
  void write(const std::string& fname) const;

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
  SF_INFO wav_info;

  //// helper functions
  bool is_wav_format() const;
  // populates samples vector from the wav
  void extract_samples(SNDFILE* wav);

  // returns the number of samples
  // in the wav indicated by wav_info
  size_t calc_num_samples() const;
};

}
}

namespace dgsnd = DG::Sound;
using dgwav = dgsnd::WAV;
