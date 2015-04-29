#include "wav_embedding_agent.hh"

void WAV_embedding_agent::embed() {
  int num_samples = outwav.get_num_samples();

  for (int i = 0; i < num_samples; ++i) {
    outwav.sample_unset_mask(i, 0x1);
    outwav.sample_set_mask(i,  set_masks[i]);
    unsigned next_index = i + 1;
    if (next_index >= set_masks.size()) {
      break;
    }
  }
}

void WAV_embedding_agent::save() const {
  outwav.write(outwav_fname);
}

std::vector<unsigned> WAV_embedding_agent::message_to_masks(const std::string& msg, Mask_type mask_type) {
  std::vector<unsigned> masks;
  std::vector<bool> msg_bits = message_to_bits(msg);

  for (int i = 0; (unsigned)i < msg_bits.size(); ++i) {
    unsigned mask = 0;
    switch (mask_type) {
    case Mask_type::SET:
      mask |= msg_bits[i];
      break;
    case Mask_type::UNSET:
      mask |= !msg_bits[i];
      break;
    }
    masks.push_back(mask);
  }
  return masks;
}

bool WAV_embedding_agent::check_msg_media_capacity(const std::string& msg) {
  unsigned num_bits = msg.length() * 8;
  unsigned num_samples = inwav.get_num_samples();
  return num_bits < num_samples;
}
