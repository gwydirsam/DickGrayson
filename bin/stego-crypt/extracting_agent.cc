#include "extracting_agent.hh"

Extracting_agent::Extracting_agent(const std::string& inbmp)
  : Extracting_agent(const std::string& inbmp, 1) { }
Extracting_agent::Extracting_agent(const std::string& inbmp, int num_lsb)
  : input(inbmp), num_lsb(num_lsb) { }

std::string extract(int num_lsb) {
  return "";
}
