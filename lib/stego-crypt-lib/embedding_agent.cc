#include "embedding_agent.hh"

Embedding_agent::Embedding_agent(const std::string& inbmp, const std::string& outbmp)
  : Embedding_agent(inbmp, outbmp, 1) { }
Embedding_agent::Embedding_agent(const std::string& inbmp, const std::string& outbmp, int num_lsb)
  : input(inbmp), output_fname(outbmp), num_lsb(num_lsb) { }

void Embedding_agent::embed_and_save(const std::string& msg) {

}
