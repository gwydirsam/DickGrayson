#include <dgtype/dgtype.hh>
#include <memory>
#include <vector>
#include <iterator>
#include <iostream>

namespace DG {
namespace Sound {

void WAV::open(const std::string& fname) {
  if (!is_file_accessible(fname)) {
    throw dgtype::Inaccessible_file("WAV");
  }
  SNDFILE* temp = sf_open(fname.c_str(), SFM_READ, &wav_info);
  if (!is_wav_format()) {
    throw dgtype::Invalid_format("WAV");
  }
  extract_samples(temp);
  sf_close(temp);
}

void WAV::write(const std::string& fname) {
  SNDFILE* temp = sf_open(fname.c_str(), SFM_WRITE, &wav_info);
  sf_write_int(temp, &samples[0], samples.size());
  sf_write_sync(temp);
  sf_close(temp);
}

void WAV::sample_set_mask(int index, unsigned mask) {
  unsigned sample = get_sample(index);
  sample |= mask;
  samples[index] = sample;
}

void WAV::sample_unset_mask(int index, unsigned mask) {
  unsigned sample = get_sample(index);
  sample &= ~mask;
  samples[index] = sample;
}

//// private member functions

bool WAV::is_wav_format() const {
  int masked_format = wav_info.format & SF_FORMAT_WAV;
  return masked_format == SF_FORMAT_WAV;
}

void WAV::extract_samples(SNDFILE* wav) {
  size_t num_samples = calc_num_samples();
  std::unique_ptr<int> temp_array(new int[num_samples]);
  sf_read_int(wav, temp_array.get(), num_samples);
  samples = std::vector<int>(temp_array.get(),
                             temp_array.get() + num_samples);
}

size_t WAV::calc_num_samples() const {
  return wav_info.frames * wav_info.channels;
}

}
}
