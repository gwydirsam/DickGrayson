// Kyle Wilson 
// Test Driven Scrumbags
// stego-attack-lib.cc

#include "stego-attack-lib.hh"

// Compare results; cannot use strcmp() because it requires signed char*
int compareHashVals(unsigned char* string1, unsigned char* string2) {
  for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    if (string1[i] != string2[i]) return 1;
  return 0;
}

// Print the MD5 sum as hex-digits.
void printMD5Sum(unsigned char* mdSum) {
  for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
    printf("%02x", mdSum[i]); // use printf for hex formatting
  }
}

// Get the size of the file by its file descriptor
unsigned long getSizeByFD(int fd) {
  struct stat statbuf;
  if (fstat(fd, &statbuf) < 0) exit(-1);
  return statbuf.st_size;
}

// Gets a single file's hash and stores it in the parameter result
void getMD5Hash(char* filename, unsigned char* hash, bool print) {
  int fileDesc;
  unsigned long fileSize;
  char* fileBuffer;

  fileDesc = open(filename, O_RDONLY);
  if (fileDesc < 0) exit(-1);

  fileSize = getSizeByFD(fileDesc);

  fileBuffer = (char*) mmap(0, fileSize, PROT_READ, MAP_SHARED, fileDesc, 0);
  MD5((unsigned char*)fileBuffer, fileSize, hash);
  munmap(fileBuffer, fileSize); 

  if (print) {
    printMD5Sum(hash);
	std::cout << filename << std::endl;
  }

}

// Determines whether or not two files have the same md5 hash
bool isEncrypted(char* img1, char* img2, bool print) {
  unsigned char result1[MD5_DIGEST_LENGTH];
  unsigned char result2[MD5_DIGEST_LENGTH];

  getMD5Hash(img1, result1, print);
  getMD5Hash(img2, result2, print);
  if (compareHashVals(result1, result2)) return true;

  else return false;
}

// Get encrypted message from wav using Martin's library
std::string retrieveWAVMessage() {
  // If isEncrypted, use Extracting_agent to get message
  // Else, return empty string
  return ""; 
}
 
// Get encrypted message from bmp using Martin's library
std::string retrieveBMPMessage() { 
  // If isEncrypted, use Extracting_agent to get message
  // Else, return empty string
  return ""; 
}

// WRITE INTERFACE //

// Randomize wav LSBs
void scrambleWAV() {
  // Calculate number of embeddable characters using WAV::get_num_samples() / 8
  // Generate a random string of that size and embed it in the image using an Embedding_agent and embed_and_save()
}

// Randomize bmp LSBs
void scrambleBMP() {
  // Calculate number of embeddable characters using ( BMP::get_num_pixels() * BMP::get_bpp() ) / 8
  // Generate a random string of that size and embed it in the image using an Embedding_agent and embed_and_save()
  }