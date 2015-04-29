#pragma once

#include <dgsnd/dgsnd.hh>
#include "abstract_extracting_agent.hh"

class WAV_extracting_agent : public Abstract_extracting_agent {
public:
  WAV_extracting_agent(std::string inwav_fname) : inwav(inwav_fname) {}

  virtual std::string extract() const override;

private:
  dgwav inwav;

  //// private helper functions

  // returns true when the lsb is 1, false otherwise
  bool extract_bit_from_sample(int index) const;
};
