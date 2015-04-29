#include <dgtype/dgtype.hh>
#include <memory>
#include <vector>
#include <iterator>
#include <iostream>
#include <cassert>

namespace DG {
namespace Sound {

void WAV::open(const std::string& fname) {
  if (!is_file_accessible(fname)) {
    throw dgtype::Inaccessible_file("WAV");
  }
  SNDFILE* temp = sf_open(fname.c_str(), SFM_READ, &wav_info);
  if (!is_format_supported()) {
    throw dgtype::Invalid_format("WAV");
  }
  extract_samples(temp);
  sf_close(temp);
}

void WAV::write(const std::string& fname) const {
  SF_INFO temp_info = wav_info;
  SNDFILE* temp = sf_open(fname.c_str(), SFM_WRITE, &temp_info);
  sf_write_short(temp, &samples[0], samples.size());
  //sf_write_sync(temp);
  sf_close(temp);
}

void WAV::sample_set_mask(int index, unsigned mask) {
  int sample = get_sample(index);
  sample |= mask;
  samples[index] = sample;
}

void WAV::sample_unset_mask(int index, unsigned mask) {
  unsigned sample = get_sample(index);
  sample &= ~mask;
  samples[index] = sample;
}

//// private member functions

bool WAV::is_format_supported() const {
  int wav_mask = wav_info.format & SF_FORMAT_WAV;
  int pcm16_mask = wav_info.format & SF_FORMAT_PCM_16;
  bool is_wav = wav_mask == SF_FORMAT_WAV;
  bool is_pcm16 = pcm16_mask == SF_FORMAT_PCM_16;
  return is_wav && is_pcm16;
}

void WAV::extract_samples(SNDFILE* wav) {
  size_t num_samples = calc_num_samples();
  std::unique_ptr<short> temp_array(new short[num_samples]);
  sf_read_short(wav, temp_array.get(), num_samples);
  samples = std::vector<short>(temp_array.get(),
                             temp_array.get() + num_samples);
}

size_t WAV::calc_num_samples() const {
  return wav_info.frames * wav_info.channels;
}

}
}
