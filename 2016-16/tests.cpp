#include <memory>
#include <sstream>
#include <gtest/gtest.h>

#include <cassert>
#include <string>

namespace AoC {
    class Dragon {
    public:
        static std::string expand(std::string a) {
            std::string result = a + '0';
            for (auto iter = a.rbegin(); a.rend() != iter; iter++) {
                if (*iter == '0') {
                    result += '1';
                } else if (*iter == '1') {
                    result += '0';
                } else {
                    assert(false);
                }
            }
            return result;
        }

        static std::string generate(std::string initial, int length) {
            std::string result = initial;
            while (result.length() < length) {
                result = expand(result);
            }
            return result.substr(0, length);
        }

        static std::string checksum(std::string input) {
            std::string result;
            for (int i = 0; i < input.length(); i += 2) {
                if (input.at(i) == input.at(i + 1)) {
                    result += '1';
                } else {
                    result += '0';
                }
            }
            if (0 == (result.length() % 2)) {
                return checksum(result);
            } else {
                return result;
            }
        }
    };
}

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
