#include <cstdint>
#include <iostream>
#include <cassert>
#include "embedding_agent.hh"

//// constructors

Embedding_agent::Embedding_agent(const std::string& inbmp_fname,
                                 const std::string& outbmp_fname)
    : inbmp(inbmp_fname), outbmp(inbmp), outbmp_fname(outbmp_fname) {}

//// public member functions

void Embedding_agent::embed_and_save(const std::string& msg) {
  std::string null_terminated_msg(std::move(msg));
  null_terminated_msg += '\0'; // will use this as a termination symbol during extraction

  if (!check_msg_bmp_capacity(msg)) {
    throw msg_too_long;
  }
  std::vector<unsigned> set_masks =
    message_to_masks(null_terminated_msg, Mask_type::SET);
  std::vector<unsigned> unset_masks =
    message_to_masks(null_terminated_msg, Mask_type::UNSET);

  int width = outbmp.get_width();
  int height = outbmp.get_height();

  bool done = false;
  int k = 0;
  for (int i = 0; i < height && !done; ++i) {
    for (int j = 0; j < width && !done; ++j) {
      outbmp.pixel_set_mask(j, i, set_masks[k]);
      outbmp.pixel_unset_mask(j, i, unset_masks[k]);
      unsigned next_index = k + 1;
      ++k;
      if (next_index >= set_masks.size()) {
        done = true;
      }
    }
  }
  outbmp.write(outbmp_fname);
}

//// private member functions

std::vector<unsigned> Embedding_agent::message_to_masks(const std::string& msg, Mask_type mask_type) {
  std::vector<unsigned> masks;
  std::vector<bool> msg_bits = message_to_bits(msg);

  int msg_bits_per_mask = outbmp.get_bpp() / 8; // (msg) bits per mask

  for (int i = 0; (unsigned)i < msg_bits.size(); i += msg_bits_per_mask) {
    unsigned mask = 0;
    for (int j = msg_bits_per_mask - 1;
         j >= 0 && (unsigned)(i + j) < msg_bits.size();
         --j) {
      switch (mask_type) {
      case Mask_type::SET:
        mask |= (msg_bits[i + j] << (j * 8));
        break;
      case Mask_type::UNSET:
        mask |= (!msg_bits[i + j] << (j * 8));
        break;
      }
    }
    masks.push_back(mask);
  }
  assert(masks.size() == msg_bits.size() / 8);
  return masks;
}

std::vector<bool> Embedding_agent::message_to_bits(const std::string& msg) {
  std::vector<bool> bits;
  for (int i = 0; (unsigned)i < msg.length(); ++i) {
    uint8_t c = msg[i];
    for (int j = 7; j >= 0; --j) {
      unsigned bit = (c >> j) & 0x1;
      bits.push_back(bit && 0x1);
    }
  }
  for (auto bit : bits) {
    std::cout << bit;
  }
  std::cout << std::endl;
  return bits;
}

bool Embedding_agent::check_msg_bmp_capacity(const std::string& msg) {
  unsigned num_bits = msg.length() * 8;
  unsigned subpixels_per_pixel = inbmp.get_bpp() / 8;
  unsigned num_pixels = inbmp.get_num_pixels();
  return num_bits < subpixels_per_pixel * num_pixels;
}
