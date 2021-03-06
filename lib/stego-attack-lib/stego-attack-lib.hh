#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <time.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <random>
#include <memory>
#include <openssl/md5.h>
#include "../stego-crypt-lib/stego-crypt-lib.hh"

// Compare results; cannot use strcmp() because it requires signed char*
int compareHashVals(unsigned char* string1, unsigned char* string2);

// Print the MD5 sum as hex-digits.
void printMD5Sum(unsigned char* md);

// Get the size of the file by its file descriptor
unsigned long getSizeByFD(int fd);

// Gets a single file's hash and stores it in the parameter result
void getMD5Hash(char* filename, unsigned char* result);

// Determines whether or not two files have the same md5 hash
bool isEncrypted(char* img1, char* img2, bool print);

// Get encrypted message from bmp or wav using Martin's library
std::string retrieveMessage(std::string orig, std::string alt);

// Randomize wav LSBs	
std::string scrambleLSB(std::string file);