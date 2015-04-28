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
