#include <memory>
#include <sstream>
#include <gtest/gtest.h>
#include "ElfGame.h"

using namespace AoC;

TEST(ElfGameTest, TestFiveElves) {
    ASSERT_EQ(3, ElfGame::play(5, [](int index, int count) -> int {
        return (index + 1) % count;
    }));
}

TEST(ElfGameTest, TestFiveElvesNewRules) {
    ASSERT_EQ(2, ElfGame::play(5, [](int index, int count) -> int {
        return (index + (count / 2)) % count;
    }));
}
