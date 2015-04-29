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

enum class Media_type {
  WAV, BMP
};

::testing::AssertionResult is_message_uncompromised(std::string test_string,
                                                    std::string in_fname,
                                                    std::string stego_fname,
                                                    Media_type type
                                                    ) {
  std::unique_ptr<Abstract_embedding_agent> embedder;
  std::unique_ptr<Abstract_extracting_agent> extractor;

  if (type == Media_type::BMP) {
    embedder = std::make_unique<BMP_embedding_agent>(in_fname, stego_fname);
  } else {
    embedder = std::make_unique<WAV_embedding_agent>(in_fname, stego_fname);
  }

  embedder->embed_and_save(test_string);

  if (type == Media_type::BMP) {
    extractor = std::make_unique<BMP_extracting_agent>(stego_fname);
  } else {
    extractor = std::make_unique<WAV_extracting_agent>(stego_fname);
  }

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
                                       locations.stegobmp,
                                       Media_type::BMP));
}

TEST(StegoCryptBMP, LSBLong) {
  EXPECT_TRUE(is_message_uncompromised(messages.longmsg,
                                       locations.testbmp,
                                       locations.stegobmp,
                                       Media_type::BMP));
}

TEST(StegoCryptWAV, LSBShort) {
  EXPECT_TRUE(is_message_uncompromised(messages.shortmsg,
                                       locations.testwav,
                                       locations.stegowav,
                                       Media_type::WAV));
}

TEST(StegoCryptWAV, LSBLong) {
  EXPECT_TRUE(is_message_uncompromised(messages.longmsg,
                                       locations.testwav,
                                       locations.stegowav,
                                       Media_type::WAV));
}

