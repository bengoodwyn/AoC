#include <memory>
#include <sstream>
#include <gtest/gtest.h>

#include <string>

namespace AoC {
    class Scrambler {
    public:
        Scrambler(std::string input) {

        }
    };
}

using namespace AoC;

TEST(ScramblerTest, CanCreateAScrambler) {
    Scrambler scrambler("foo");
}
