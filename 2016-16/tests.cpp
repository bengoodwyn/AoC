#include <memory>
#include <sstream>
#include <gtest/gtest.h>

#include "Dragon.h"

using namespace AoC;

class DragonTest : public ::testing::Test {
public:
    virtual void SetUp() override {
        dragon.reset(new Dragon());
    }

    virtual void TearDown() override {
        dragon.reset();
    }

    std::unique_ptr<Dragon> dragon;
};

TEST_F(DragonTest, ExpansionTests) {
    ASSERT_EQ("100", Dragon::expand("1"));
    ASSERT_EQ("001", Dragon::expand("0"));
    ASSERT_EQ("11111000000", Dragon::expand("11111"));
    ASSERT_EQ("1111000010100101011110000", Dragon::expand("111100001010"));
}

TEST_F(DragonTest, GenerateTest) {
    ASSERT_EQ("10000011110010000111", Dragon::generate("10000", 20));
}

TEST_F(DragonTest, ChecksumTest) {
    ASSERT_EQ("01100", Dragon::checksum("10000011110010000111"));
}
