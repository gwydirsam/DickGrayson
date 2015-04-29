#include "wav_extracting_agent.hh"

std::string WAV_extracting_agent::extract() const {
  std::string msg;
  std::vector<bool> msg_bits;

  int num_samples = inwav.get_num_samples();
  for (int i = 0; i < num_samples; ++i) {
    bool bit = extract_bit_from_sample(i);
    msg_bits.push_back(bit);
    if (is_last_byte_terminate(msg_bits)) {
      msg_bits.pop_back();
      return bits_to_string(msg_bits);
    }
  }
  return msg;
}

bool WAV_extracting_agent::extract_bit_from_sample(int index) const {
  int sample = inwav.get_sample(index);
  int bit = sample & 0x1;
  return bit == 0x1;
}
