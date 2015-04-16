#pragma once

#include <dgimg/dgimg.hh>

class Embedding_agent {
  // takes a bmp inbmp, and embeds data into it, saving the image
  // with embedded data to outbmp
public:
  enum class LSB_encoding { Null_encoding = 0 }; // stub
  
  Embedding_agent() = delete;
  Embedding_agent(const std::string& inbmp, const std::string& outbmp);
  Embedding_agent(const std::string& inbmp, const std::string& outbmp, int num_lsb);

  // Embeds msg into output and writes the bmp out to disk
  void embed_and_save(const std::string& msg);

  double mean_squared_error();
  double peak_signal_noise_ratio();

  void set_lsb(int n) { num_lsb = n; }
private:
  dgbmp input;
  dgbmp output;
  int num_lsb; // number of least significant bits
}
