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
    ASSERT_EQ("100", dragon->expand("1"));
    ASSERT_EQ("001", dragon->expand("0"));
    ASSERT_EQ("11111000000", dragon->expand("11111"));
    ASSERT_EQ("1111000010100101011110000", dragon->expand("111100001010"));
}
