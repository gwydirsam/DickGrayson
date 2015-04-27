#pragma once

#include <vector>
#include <exception>
#include <dgimg/dgimg.hh>

class Embedding_agent {
  // takes an input bmp, and embeds data into it, saving the image
  // with embedded data to an output bmp
 public:

  struct Msg_too_long_for_media_exception : public std::exception {
    virtual const char* what() const throw() {
      return "Munchkin-steg: Msg_too_long_for_media_exception";
    }
  } msg_too_long;

  Embedding_agent() = delete;

  Embedding_agent(const std::string& inbmp_fname,
                  const std::string& outbmp_fname);

  // Embeds msg into output and writes the bmp out to disk
  void embed_and_save(const std::string& msg);

 private:
  dgbmp inbmp;
  dgbmp outbmp;
  std::string outbmp_fname;

  enum class Mask_type { SET, UNSET };

  //// helper functions

  // Takes a message and returns a list of bit masks based on the
  // bits per pixel (bpp) of the input bmp
  std::vector<unsigned> message_to_masks(const std::string& msg, Mask_type mask_type);

  std::vector<bool> message_to_bits(const std::string& msg);

  // returns true when the message can fit within the bmp
  bool check_msg_bmp_capacity(const std::string& msg);
};
