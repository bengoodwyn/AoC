#include <memory>
#include <gtest/gtest.h>
#include "KeyGenerator.h"

using namespace AoC;

class KeyGeneratorTests : public ::testing::Test {
public:
    virtual void SetUp() override {
        keyGenerator.reset(new KeyGenerator("abc", 0));
    }

    virtual void TearDown() override {
        keyGenerator.reset();
    }

    std::unique_ptr<KeyGenerator> keyGenerator;
};

TEST_F(KeyGeneratorTests, CanCombineSaltWithIntegerIndex) {
    ASSERT_EQ("abc123", keyGenerator->saltInteger(123));
}

TEST_F(KeyGeneratorTests, CanGetDigestOfAString) {
    ASSERT_EQ("0034e0923cc38887a57bd7b1d4f953df", std::string(keyGenerator->digest("abc18")));
}

TEST_F(KeyGeneratorTests, CanFindATripleInAString) {
    ASSERT_EQ('x', keyGenerator->findTriple("fooxxxbar"));
}

TEST_F(KeyGeneratorTests, DoesntFindTripleInStringsWithoutTriples) {
    ASSERT_EQ('\0', keyGenerator->findTriple("fooxbarxxforbarx"));
}

TEST_F(KeyGeneratorTests, CanFindAQuintupleOfAGivenCharacter) {
    ASSERT_TRUE(keyGenerator->findQuintuple("fooxxxxxbar", 'x'));
}

TEST_F(KeyGeneratorTests, CanNotFindAQuintupleOfAGivenCharacter) {
    ASSERT_FALSE(keyGenerator->findQuintuple("fooxxxxxbar", 'y'));
}

TEST_F(KeyGeneratorTests, CanGetIndexOfNthKey) {
    ASSERT_EQ(22728, keyGenerator->indexOfKey(64));
}
