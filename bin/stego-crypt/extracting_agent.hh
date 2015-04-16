#pragma once

class Extracting_agent {
public:
  Extracting_agent(const std::string& inbmp);

  std::string extract() const;
private:
  dgbmp intput;
}
