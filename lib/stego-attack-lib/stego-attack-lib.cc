#include "stego-attack-lib.hh"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <openssl/md5.h>

unsigned char result1[MD5_DIGEST_LENGTH];
unsigned char result2[MD5_DIGEST_LENGTH];

// Compare results; cannot use strcmp() because it requires signed char*
int compareHashVals(unsigned char* string1, unsigned char* string2) {
  int i;
  for (i = 0; i < MD5_DIGEST_LENGTH; i++)
    if (string1[i] != string2[i]) return 1;
  return 0;
}

// Print the MD5 sum as hex-digits.
void printMD5Sum(unsigned char* md) {
  int i;
  for (i = 0; i < MD5_DIGEST_LENGTH; i++) {
    printf("%02x", md[i]);
  }
}

// Get the size of the file by its file descriptor
unsigned long getSizeByFD(int fd) {
  struct stat statbuf;
  if (fstat(fd, &statbuf) < 0) exit(-1);
  return statbuf.st_size;
}

// Gets a single file's hash and stores it in the parameter result
void getMD5Hash(char* filename, unsigned char* result) {
  int fileDesc;
  unsigned long fileSize;
  char* fileBuffer;

  fileDesc = open(filename, O_RDONLY);
  if (fileDesc < 0) exit(-1);

  fileSize = getSizeByFD(fileDesc);

  fileBuffer = (char*)mmap(0, fileSize, PROT_READ, MAP_SHARED, fileDesc, 0);
  MD5((unsigned char*)fileBuffer, fileSize, result);
  munmap(fileBuffer, fileSize);

  printMD5Sum(result);
  printf("  %s\n", filename);
}

// Run: ./md5attack <original image file> <new image file>
// int main(int argc, char *argv[]) {

//     if(argc != 3) {
//             printf("Must specify the files\n");
//             exit(-1);
//     }
//     getMD5Hash(argv[1], result1);
//     getMD5Hash(argv[2], result2);

//     if (compareHashVals(result1, result2)) {
//     	printf("Hashes do not match: There is a message embedded!\n");
//     }
//     else printf("Hashes match: There is no embedded message.\n");

//     return 0;
// }
