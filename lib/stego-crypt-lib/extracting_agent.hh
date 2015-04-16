#pragma once

class Extracting_agent {
public:
  Extracting_agent() = delete;
  Extracting_agent(const std::string& inbmp);

  std::string extract(int num_lsb) {
    return "";
  }
private:
  dgbmp input;
  int num_lsb;
}
