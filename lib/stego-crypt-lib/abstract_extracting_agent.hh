#pragma once

#include <vector>
#include <dgimg/dgimg.hh>

class Abstract_extracting_agent {
 public:

  virtual std::string extract() const = 0;

 protected:
  //// helper functions

  bool is_last_byte_terminate(const std::vector<bool>& bits) const;
  std::string bits_to_string(const std::vector<bool>& bits) const;
};
