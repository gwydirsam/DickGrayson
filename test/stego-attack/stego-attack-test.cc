#include <gtest/gtest.h>
#include <stego-attack-lib/stego-attack-lib.hh>

TEST(totoStub, oneEqualsOne) {
 int i = 1;
 EXPECT_EQ(1, i);
}

TEST(StegoAttack, compareHashVals) {
 std::string string1 = "Hello poppet.";
 std::string string2 = "Jello muppet.";
 unsigned char* uc1 = (unsigned char*)string1.c_str();
 unsigned char* uc2 = (unsigned char*)string2.c_str();
 EXPECT_EQ(1 ,compareHashVals(uc1,uc2));
}

TEST(StegoAttackImage, differentFiles) {
  bool result = isEncrypted("../../test/stego-attack/fluffy1.png", "../../test/stego-attack/fluffy2.png", false);
  EXPECT_EQ(true, result);
}

TEST(StegoAttackImage, sameFileSameName) {
  EXPECT_EQ(false, isEncrypted("../../test/stego-attack/fluffy1.png","../../test/stego-attack/fluffy1.png", false));
}

TEST(StegoAttackImage, sameFileDifferentName) {
  EXPECT_EQ(false, isEncrypted("../../test/stego-attack/fluffy1.png","../../test/stego-attack/fluffy3.png", false));
}

TEST(StegoAttackAudio, differentFiles) {
  EXPECT_EQ(true, isEncrypted("../../test/stego-attack/clarinocrypt.wav","../../test/stego-attack/claricrypt.wav", false));
}

TEST(StegoAttackAudio, sameFiles) {
  EXPECT_EQ(false, isEncrypted("../../test/stego-attack/clarinocrypt.wav","../../test/stego-attack/clarinocrypt.wav", false));
}
