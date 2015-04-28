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
  data = sf_open(fname.c_str(), SFM_READ, &data_info);
  if (!is_wav_format()) {
    throw dgtype::Invalid_format("WAV");
  }
  extract_samples();
}

void WAV::write(const std::string& fname) {
  std::move(fname); // do fun things until we define this function
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
  int masked_format = data_info.format & SF_FORMAT_WAV;
  return masked_format == SF_FORMAT_WAV;
}

void WAV::extract_samples() {
  size_t num_samples = calc_num_samples();
  std::unique_ptr<int> temp_array(new int[num_samples]);
  sf_read_int(data, temp_array.get(), num_samples);
  samples = std::vector<int>(temp_array.get(),
                             temp_array.get() + num_samples);
}

size_t WAV::calc_num_samples() const {
  return data_info.frames * data_info.channels;
}

}
}
