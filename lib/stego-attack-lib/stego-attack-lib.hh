#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <openssl/md5.h>

// Compare results; cannot use strcmp() because it requires signed char*
int compareHashVals(unsigned char* string1, unsigned char* string2);

// Print the MD5 sum as hex-digits.
void printMD5Sum(unsigned char* md);

// Get the size of the file by its file descriptor
unsigned long getSizeByFD(int fd);

// Gets a single file's hash and stores it in the parameter result
void getMD5Hash(char* filename, unsigned char* result);
