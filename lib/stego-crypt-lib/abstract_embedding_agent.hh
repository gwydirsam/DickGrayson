#pragma once

#include <vector>
#include <exception>
#include <dgimg/dgimg.hh>

class Abstract_embedding_agent {
  // takes an input bmp, and embeds data into it, saving the image
  // with embedded data to an output bmp
public:

  struct Msg_too_long_for_media_exception : public std::exception {
    virtual const char* what() const throw() {
      return "Munchkin-steg: Msg_too_long_for_media_exception";
    }
  } msg_too_long;

  Abstract_embedding_agent() { }

  // Embeds msg into output and writes the bmp out to disk
  void embed_and_save(const std::string& msg);

protected:

  std::vector<unsigned> set_masks;
  std::vector<unsigned> unset_masks;

  enum class Mask_type { SET, UNSET };

  //// protected helper functions

  // Takes a message and returns a list of bit masks based on the
  // bits per pixel (bpp) of the input bmp
  virtual std::vector<unsigned> message_to_masks(const std::string& msg, Mask_type mask_type) = 0;

  // returns true when the message can fit within the bmp
  virtual bool check_msg_bmp_capacity(const std::string& msg) = 0;

  // embeds message into the outbmp
  virtual void embed() = 0;

  // saves outbmp to outbmp_fname
  virtual void save() const = 0;

  std::vector<bool> message_to_bits(const std::string& msg);

private:
  //// private helper functions

  // generates the set and unset masks vectors
  void generate_masks(const std::string& msg);
};
