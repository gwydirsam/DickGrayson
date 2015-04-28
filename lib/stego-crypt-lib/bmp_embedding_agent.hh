#include <string>
#include "abstract_embedding_agent.hh"
#include <dgimg/dgimg.hh>

class BMP_embedding_agent : public Abstract_embedding_agent {
public:
  BMP_embedding_agent() = delete;
  BMP_embedding_agent(std::string inbmp_fname, std::string outbmp_fname)
    : inbmp(inbmp_fname), outbmp(inbmp), outbmp_fname(outbmp_fname) { }

protected:
  //// protected helper functions

  // Takes a message and returns a list of bit masks based on the
  // bits per pixel (bpp) of the input bmp
  virtual std::vector<unsigned> message_to_masks(const std::string& msg
                                                 , Mask_type mask_type) override;

  // returns true when the message can fit within the bmp
  virtual bool check_msg_bmp_capacity(const std::string& msg) override;

  // embeds message into the outbmp
  virtual void embed() override;

  // saves outbmp to outbmp_fname
  virtual void save() const override;

private:
  dgbmp inbmp, outbmp;
  std::string outbmp_fname;
};

inline void BMP_embedding_agent::embed() {
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
}

inline void BMP_embedding_agent::save() const {
  outbmp.write(outbmp_fname);
}

inline std::vector<unsigned> BMP_embedding_agent::message_to_masks(const std::string& msg, Mask_type mask_type) {
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
  return masks;
}

inline bool BMP_embedding_agent::check_msg_bmp_capacity(const std::string& msg) {
  unsigned num_bits = msg.length() * 8;
  unsigned subpixels_per_pixel = inbmp.get_bpp() / 8;
  unsigned num_pixels = inbmp.get_num_pixels();
  return num_bits < subpixels_per_pixel * num_pixels;
}
