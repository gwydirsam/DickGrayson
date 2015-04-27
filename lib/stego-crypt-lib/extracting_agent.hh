#pragma once

#include <vector>
#include <dgimg/dgimg.hh>

class Extracting_agent {
 public:
  Extracting_agent() = delete;
  Extracting_agent(const std::string& inbmp_fname);

  std::string extract() const;

 private:
  dgbmp inbmp;

  //// helper functions

  std::vector<bool> extract_bits_from_pixel(int x, int y) const;
  bool is_last_byte_terminate(const std::vector<bool>& bits) const;
  std::string bits_to_string(const std::vector<bool>& bits) const;
};
