#include <gtest/gtest.h>
#include <stego-attack-lib/stego-attack-lib.hh>

TEST(StegoAttackImage, differentFiles) {
  EXPECT_EQ(true, isEncrypted("../../test/stego_attack/fluffy1.png","../../test/stego_attack/fluffy2.png", false));
}

TEST(StegoAttackImage, sameFileSameName) {
  EXPECT_EQ(false, isEncrypted("../../test/stego_attack/fluffy1.png","../../test/stego_attack/fluffy1.png", false));
}

TEST(StegoAttackImage, sameFileDifferentName) {
  EXPECT_EQ(false, isEncrypted("../../test/stego_attack/fluffy1.png","../../test/stego_attack/fluffy3.png", false));
}

TEST(StegoAttackAudio, differentFiles) {
  EXPECT_EQ(true, isEncrypted("../../test/stego_attack/clarinocrypt.wav","../../test/stego_attack/claricrypt.wav", false));
}

TEST(StegoAttackAudio, sameFiles) {
  EXPECT_EQ(false, isEncrypted("../../test/stego_attack/clarinocrypt.wav","../../test/stego_attack/clarinocrypt.wav", false));
}
