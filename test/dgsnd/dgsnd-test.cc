#include <gtest/gtest.h>
#include <dgtype/dgtype.hh>

TEST(Wav, InvalidFormatException) {
  EXPECT_THROW(dgwav wav("../../test/dgsnd/badformat.mp3"),
               dgtype::Invalid_format_exception);
}

TEST(Wav, InaccessibleFileException) {
  EXPECT_THROW(dgwav wav("imaginary.wav"),
               dgtype::Inaccessible_file_exception);
}

TEST(Wav, SampleSetMask) {
  dgwav wav("../../test/dgsnd/test.wav");
  unsigned first_sample = wav.get_sample(0);

  wav.sample_set_mask(0, 0x0u);
  EXPECT_EQ(first_sample, wav.get_sample(0));

  wav.sample_set_mask(0, 0xFFFFFFFFu);
  EXPECT_EQ(0xFFFFFFFFu, wav.get_sample(0));
}

TEST(Wav, SampleUnsetMask) {
  dgwav wav("../../test/dgsnd/test.wav");
  unsigned first_sample = wav.get_sample(0);

  wav.sample_unset_mask(0, 0x0u);
  EXPECT_EQ(first_sample, wav.get_sample(0));

  wav.sample_unset_mask(0, 0xFFFFFFFFu);
  EXPECT_EQ(0x0u, wav.get_sample(0));
}
