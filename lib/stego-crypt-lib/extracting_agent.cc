#include "extracting_agent.hh"

Extracting_agent::Extracting_agent(const std::string& inbmp, int num_lsb)
    : input(inbmp), num_lsb(num_lsb) {}

Extracting_agent::Extracting_agent(const std::string& inbmp)
    : Extracting_agent(inbmp, 1) {}

std::string Extracting_agent::extract() const { return ""; }
