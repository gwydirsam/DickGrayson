#include <memory>
#include <cstdint>
#include <iostream>
#include "abstract_embedding_agent.hh"
#include "bmp_embedding_agent.hh"
#include "wav_embedding_agent.hh"
#include "file_io.hh"

//// constructors

//// public member functions

void Abstract_embedding_agent::embed_and_save(const std::string& msg) {
  if (!check_msg_media_capacity(msg)) {
    throw msg_too_long;
  }

  std::string null_terminated_msg(std::move(msg));
  null_terminated_msg += '\0'; // will use this as a termination symbol during extraction
  generate_masks(null_terminated_msg);

  embed();
  save();
}

void Abstract_embedding_agent::generate_masks(const std::string& msg) {
  set_masks = message_to_masks(msg, Mask_type::SET);
  unset_masks = message_to_masks(msg, Mask_type::UNSET);
}

std::vector<bool> Abstract_embedding_agent::message_to_bits(const std::string& msg) {
  std::vector<bool> bits;
  for (int i = 0; (unsigned)i < msg.length(); ++i) {
    uint8_t c = msg[i];
    for (int j = 7; j >= 0; --j) {
      unsigned bit = (c >> j) & 0x1;
      bits.push_back(bit == 0x1u);
    }
  }
  return bits;
}

std::unique_ptr<Abstract_embedding_agent> which_embedding_agent(std::string inmedia_fname,
                                                                std::string outmedia_fname) {
  std::unique_ptr<Abstract_embedding_agent> embedder;

  File_type type = file_type_of(inmedia_fname);

  if (type == File_type::BMP) {
    embedder =
      std::make_unique<BMP_embedding_agent>(inmedia_fname, outmedia_fname);
  } else {
    embedder =
      std::make_unique<WAV_embedding_agent>(inmedia_fname, outmedia_fname);
  }
  return embedder;
}
