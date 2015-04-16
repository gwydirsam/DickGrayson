#pragma once

#include <dgimg/dgimg.hh>

class Extracting_agent {
public:
  Extracting_agent() = delete;
  Extracting_agent(const std::string& inbmp, int num_lsb);
  Extracting_agent(const std::string& inbmp);

  std::string extract() const;
private:
  dgbmp input;
  int num_lsb;
};
