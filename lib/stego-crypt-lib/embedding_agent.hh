#pragma once

#include <dgimg/dgimg.hh>

class Embedding_agent {
  // takes a bmp inbmp, and embeds data into it, saving the image
  // with embedded data to outbmp
public:
  enum class LSB_encoding : unsigned { 
    LSB1=0x01,
    LSB2=0x03,
    LSB3=0x07,
    LSB4=0x0F,
    LSB5=0x1F,
    LSB6=0x3F,
    LSB7=0x7F,
    LSB8=0xFF
  };

  Embedding_agent() = delete;
  Embedding_agent(const std::string& inbmp, const std::string& outbmp);
  Embedding_agent(const std::string& inbmp, const std::string& outbmp, int num_lsb);

  // Embeds msg into output and writes the bmp out to disk
  void embed_and_save(const std::string& msg);
private:
  dgbmp input;
  dgbmp output;
  std::string output_fname;
  int num_lsb; // number of least significant bits
};
