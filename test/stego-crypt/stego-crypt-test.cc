#include <gtest/gtest.h>
#include <stego-crypt-lib/stego-crypt-lib.hh>

TEST(StegoCryptBMP, LSB) {
  std::string test_string = "The quick brown fox jumped over the lazy dog.";
  Embedding_agent embedder("../../test/stego-crypt/test.bmp",
                           "../../test/stego-crypt/test-stego.bmp");
  embedder.embed_and_save(test_string);

  Extracting_agent extractor("../../test/stego-crypt/test-stego.bmp");
  std::string extracted_string = extractor.extract();

  EXPECT_EQ(test_string, extracted_string);
}
