#include <string>

std::string base64_encode(char const* bytes_to_encode, unsigned int len);
std::string base64_decode(std::string const& s);
