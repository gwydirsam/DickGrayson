#pragma once

#include <string>
#include <dgimg/dgimg.hh>
#include "abstract_extracting_agent.hh"

class BMP_extracting_agent : public Abstract_extracting_agent {
public:
  BMP_extracting_agent(std::string inbmp_fname) : inbmp(inbmp_fname) {}

  virtual std::string extract() const override;

private:
  dgbmp inbmp;

  //// private helper functions

  std::vector<bool> extract_bits_from_pixel(int x, int y) const;
};
