#include <memory>
#include <sstream>
#include <gtest/gtest.h>

#include <string>

namespace AoC {
    class Scrambler {
    public:
        Scrambler(std::string input) : input(input) {

        }

        std::string result() {
            return input;
        }

    private:
        std::string input;
    };
}

using namespace AoC;

TEST(ScramblerTest, CanCreateAScramblerAndGetAResult) {
    Scrambler scrambler("foo");
    ASSERT_EQ("foo", scrambler.result());
}
