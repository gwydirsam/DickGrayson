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
	std::cout << ": " << filename << std::endl;
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
std::string retrieveMessage(std::string orig, std::string alt) {
  // Throw exceptions in error cases if necessary
  if (isEncrypted((char*)orig.c_str(), (char*)alt.c_str(), false)) {
      std::unique_ptr<Abstract_extracting_agent> extractor;
      extractor = which_extracting_agent(alt);
      return extractor->extract();
  }
  else return "";
}
 
// WRITE INTERFACE //
// in interface, if extract is called on file w/ extension != '.wav' && '.bmp'
// return error message (maybe not)

// Randomize wav LSBs
// 1) How to get length
// 2) Can I use same file for both embedder params (yes)

std::string scrambleLSB(std::string file) {
  // Catch exceptions and throw error
  // Inaccessable_file_exception
  // Invalid_format_exception
  int length = 0; 
  if (file_type_of(file) == File_type::WAV) {
    dgwav origWAV(file);
    length = origWAV.get_num_samples() / 8;
  }
  else if (file_type_of(file) == File_type::BMP) {
    dgbmp origBMP(file);
    length = (origBMP.get_num_pixels() * origBMP.get_bpp()) / 64;
  }
  else return "";
  char temp[length];
  srand(time(NULL));
  for (int i = 0; i < length; i++) {
    temp[i] = 1 + rand()%126; // generate basic ASCII character (1-126)
  }
  temp[length] = 0;
  std::string randomChars = temp;
  std::unique_ptr<Abstract_embedding_agent> embedder;
  embedder = which_embedding_agent(file, file);
  embedder->embed_and_save(randomChars);
  return randomChars;
}

