#include <gtest/gtest.h>
#include <stego-crypt-lib/stego-crypt-lib.hh>

TEST(StegoCryptBMP, LSBShort) {
  std::string test_string = "The quick brown fox jumped over the lazy dog.";
  Embedding_agent embedder("../../test/stego-crypt/test.bmp",
                           "../../test/stego-crypt/test-stego.bmp");
  embedder.embed_and_save(test_string);

  Extracting_agent extractor("../../test/stego-crypt/test-stego.bmp");
  std::string extracted_string = extractor.extract();

  EXPECT_EQ(test_string, extracted_string);
}

TEST(StegoCryptBMP, LSBLong) {
  std::string test_string = "This is my message.  I like my message.  My message is totally amazing.  You can not tell\nme that my message is not amazing.  You have to admit my message is really amazing.";
  Embedding_agent embedder("../../test/stego-crypt/test.bmp",
                           "../../test/stego-crypt/test-stego.bmp");
  embedder.embed_and_save(test_string);

  Extracting_agent extractor("../../test/stego-crypt/test-stego.bmp");
  std::string extracted_string = extractor.extract();

  EXPECT_EQ(test_string, extracted_string);
}
