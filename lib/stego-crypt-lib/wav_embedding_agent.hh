#pragma once

#include "abstract_embedding_agent.hh"
#include <dgsnd/dgsnd.hh>

class WAV_embedding_agent : public Abstract_embedding_agent {
public:
  WAV_embedding_agent() = delete;
  WAV_embedding_agent(std::string inwav_fname, std::string outwav_fname)
    : inwav(inwav_fname), outwav(inwav), outwav_fname(outwav_fname) { }

protected:
  //// protected helper functions

  // Takes a message and returns a list of bit masks based on the
  // bits per pixel (bpp) of the input wav
  virtual std::vector<unsigned> message_to_masks(const std::string& msg
                                                 , Mask_type mask_type) override;

  // returns true when the message can fit within the wav
  virtual bool check_msg_media_capacity(const std::string& msg) override;

  // embeds message into the outwav
  virtual void embed() override;

  // saves outwav to outwav_fname
  virtual void save() const override;

private:
  dgwav inwav, outwav;
  std::string outwav_fname;
};
