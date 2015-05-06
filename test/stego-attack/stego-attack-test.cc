#include <gtest/gtest.h>
#include <stego-attack-lib/stego-attack-lib.hh>
// #include <stego-crypt-lib/stego-crypt-lib.hh>

TEST(totoStub, oneEqualsOne) {
 int i = 1;
 EXPECT_EQ(1, i);
}

TEST(md5Comparison, compareHashVals) {
 std::string string1 = "Hello poppet.";
 std::string string2 = "Jello muppet.";
 unsigned char* uc1 = (unsigned char*)string1.c_str();
 unsigned char* uc2 = (unsigned char*)string2.c_str();
 EXPECT_EQ(1 ,compareHashVals(uc1,uc2));
}

TEST(MD5ComparisonImage, differentFiles) {
  EXPECT_TRUE(isEncrypted("../../test/stego-attack/fluffy1.png", "../../test/stego-attack/fluffy2.png", false));
}

TEST(MD5ComparisonImage, sameFileSameName) {
  EXPECT_FALSE(isEncrypted("../../test/stego-attack/fluffy1.png","../../test/stego-attack/fluffy1.png", false));
}

TEST(MD5ComparisonImage, sameFileDifferentName) {
  EXPECT_FALSE(isEncrypted("../../test/stego-attack/fluffy1.png","../../test/stego-attack/fluffy3.png", false));
}

TEST(MD5ComparisonImage, encryptedUsingStegoCrypt) {
 std::string message = "Super secret message";
 std::string infile = "../../test/stego-attack/test.bmp";
 std::string outfile = "../../test/stego-attack/test-stego.bmp";
 std::unique_ptr<Abstract_embedding_agent> embedder;
 embedder = which_embedding_agent(infile, outfile);
 embedder->embed_and_save(message);
 EXPECT_TRUE(isEncrypted((char*)infile.c_str(), (char*)outfile.c_str(), false));  
}


TEST(MD5ComparisonAudio, differentFiles) {
  EXPECT_TRUE(isEncrypted("../../test/stego-attack/clarinocrypt.wav","../../test/stego-attack/claricrypt.wav", false));
}

TEST(MD5ComparisonAudio, sameFiles) {
  EXPECT_FALSE(isEncrypted("../../test/stego-attack/clarinocrypt.wav","../../test/stego-attack/clarinocrypt.wav", false));
}

TEST(MD5ComparisonAudio, encryptedUsingStegoCrypt) {
 std::string message = "Super secret message";
 std::string infile = "../../test/stego-attack/test.wav";
 std::string outfile = "../../test/stego-attack/test-stego.wav";
 std::unique_ptr<Abstract_embedding_agent> embedder;
 embedder = which_embedding_agent(infile, outfile);
 embedder->embed_and_save(message);
 EXPECT_TRUE(isEncrypted((char*)infile.c_str(), (char*)outfile.c_str(), false));  
}

TEST(InterfaceStub, example) {
 int i = 1;
 EXPECT_EQ(1, i);
}

TEST(Extract, standardBMPCase) {
 std::string message = "My real name is Dick Grayson.";
 std::string infile = "../../test/stego-crypt/test.bmp";
 std::string outfile = "../../test/stego-crypt/test-stego.bmp";
 std::unique_ptr<Abstract_embedding_agent> embedder;
 embedder = which_embedding_agent(infile, outfile);
 embedder->embed_and_save(message);
 EXPECT_EQ(message, retrieveMessage(infile, outfile));  
}

TEST(Extract, standardWAVCase) {
 std::string message = "Super secret message";
 std::string infile = "../../test/stego-attack/test.wav";
 std::string outfile = "../../test/stego-attack/test-stego.wav";
 std::unique_ptr<Abstract_embedding_agent> embedder;
 embedder = which_embedding_agent(infile, outfile);
 embedder->embed_and_save(message);
 EXPECT_EQ(message, retrieveMessage(infile, outfile));  
}

TEST(LSBScrambler, standardBMPCase) {
 std::string file = "../../test/stego-crypt/test-stego.bmp";
 std::string message = scrambleLSB(file);
 std::unique_ptr<Abstract_extracting_agent> extractor;
 extractor = which_extracting_agent(file);
 std::string extracted = extractor->extract();
 EXPECT_EQ(message, extracted);  
}

TEST(LSBScrambler, standardWAVCase) {
 std::string file =  "../../test/stego-attack/test-stego.wav";
 std::string message = scrambleLSB(file);
 std::unique_ptr<Abstract_extracting_agent> extractor;
 extractor = which_extracting_agent(file);
 std::string extracted = extractor->extract();
 EXPECT_EQ(message, extracted);   
}