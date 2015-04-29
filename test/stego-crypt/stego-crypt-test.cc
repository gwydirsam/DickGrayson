#include <gtest/gtest.h>
#include <stego-crypt-lib/stego-crypt-lib.hh>
#include <memory>

struct Messages {
  std::string shortmsg = "The quick brown fox jumped over the lazy dog.";
  std::string longmsg = "This is my message.  I like my message.  My message is totally amazing.  You can not tell\nme that my message is not amazing.  You have to admit my message is really amazing.";
} messages;

struct Locations {
  std::string testbmp = "../../test/stego-crypt/test.bmp";
  std::string stegobmp = "../../test/stego-crypt/test-stego.bmp";
  std::string testwav = "../../test/stego-crypt/test.wav";
  std::string stegowav = "../../test/stego-crypt/test-stego.wav";
} locations;

// This also served as an example of how to use the embedding and extracting classes
::testing::AssertionResult is_message_uncompromised(std::string test_string,
                                                    std::string in_fname,
                                                    std::string stego_fname
                                                    ) {
  std::unique_ptr<Abstract_embedding_agent> embedder;
  std::unique_ptr<Abstract_extracting_agent> extractor;

  embedder = which_embedding_agent(in_fname, stego_fname);
  embedder->embed_and_save(test_string);

  extractor = which_extracting_agent(stego_fname);
  std::string extracted_string = extractor->extract();

  if (test_string == extracted_string) {
    return ::testing::AssertionSuccess();
  } else {
    return ::testing::AssertionFailure() << "Extracted string was \""
                                         << extracted_string << '\"';
  }
}

TEST(StegoCryptBMP, LSBShort) {
  EXPECT_TRUE(is_message_uncompromised(messages.shortmsg,
                                       locations.testbmp,
                                       locations.stegobmp));
}

TEST(StegoCryptBMP, LSBLong) {
  EXPECT_TRUE(is_message_uncompromised(messages.longmsg,
                                       locations.testbmp,
                                       locations.stegobmp));
}

TEST(StegoCryptWAV, LSBShort) {
  EXPECT_TRUE(is_message_uncompromised(messages.shortmsg,
                                       locations.testwav,
                                       locations.stegowav));
}

TEST(StegoCryptWAV, LSBLong) {
  EXPECT_TRUE(is_message_uncompromised(messages.longmsg,
                                       locations.testwav,
                                       locations.stegowav));
}

