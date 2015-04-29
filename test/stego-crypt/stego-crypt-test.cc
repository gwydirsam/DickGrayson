#include <gtest/gtest.h>
#include <stego-crypt-lib/stego-crypt-lib.hh>

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

::testing::AssertionResult BMP_is_message_uncompromised(std::string test_string, std::string testbmp, std::string stegobmp) {
  BMP_embedding_agent embedder(testbmp, stegobmp);
  embedder.embed_and_save(test_string);

  BMP_extracting_agent extractor(stegobmp);
  std::string extracted_string = extractor.extract();

  if (test_string == extracted_string) {
    return ::testing::AssertionSuccess();
  } else {
    return ::testing::AssertionFailure() << "Extracted string was \"" << extracted_string << '\"';
  }
}

::testing::AssertionResult WAV_is_message_uncompromised(std::string test_string, std::string testwav, std::string stegowav) {
  WAV_embedding_agent embedder(testwav, stegowav);
  embedder.embed_and_save(test_string);

  WAV_extracting_agent extractor(stegowav);
  std::string extracted_string = extractor.extract();

  if (test_string == extracted_string) {
    return ::testing::AssertionSuccess();
  } else {
    return ::testing::AssertionFailure() << "Extracted string was \"" << extracted_string << '\"';
  }
}

TEST(StegoCryptBMP, LSBShort) {
  EXPECT_TRUE(BMP_is_message_uncompromised(messages.shortmsg, locations.testbmp, locations.stegobmp));
}

TEST(StegoCryptBMP, LSBLong) {
  EXPECT_TRUE(BMP_is_message_uncompromised(messages.longmsg, locations.testbmp, locations.stegobmp));
}

TEST(StegoCryptWAV, LSBShort) {
  EXPECT_TRUE(WAV_is_message_uncompromised(messages.shortmsg, locations.testwav, locations.stegowav));
}

TEST(StegoCryptWAV, LSBLong) {
  EXPECT_TRUE(WAV_is_message_uncompromised(messages.longmsg, locations.testwav, locations.stegowav));
}
