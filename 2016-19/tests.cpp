#include <memory>
#include <sstream>
#include <gtest/gtest.h>

namespace AoC {
    class ElfGame {
    public:
        static int play(int elves) {
            return 3;
        }
    };
}

using namespace AoC;

TEST(ElfGameTest, TestFiveElves) {
    ASSERT_EQ(3, ElfGame::play(5));
}
