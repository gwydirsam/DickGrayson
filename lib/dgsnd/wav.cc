#include <dgtype/dgtype.hh>

namespace DG {
namespace Sound {

void WAV::open(const std::string& fname) {
  if (!is_file_accessible(fname)) {
    throw dgtype::Inaccessible_file("WAV");
  }
  sf_open(fname.c_str(), SFM_READ, &data_info);
  if (!is_wav_format()) {
    throw dgtype::Invalid_format("WAV");
  }
}

void WAV::write(const std::string& fname) {
  std::move(fname); // do fun things until we define this function
}

void WAV::sample_set_mask(int index, unsigned mask) {
  // do fun things until we define this function
  std::move(index);
  std::move(mask);
}

void WAV::sample_unset_mask(int index, unsigned mask) {
  // do fun things until we define this function
  std::move(index);
  std::move(mask);
}

bool WAV::is_wav_format() const {
  int masked_format = data_info.format & SF_FORMAT_WAV;
  return masked_format == SF_FORMAT_WAV;
}

}
}
