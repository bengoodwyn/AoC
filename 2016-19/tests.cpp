#include <memory>
#include <sstream>
#include <gtest/gtest.h>
#include "ElfGame.h"

using namespace AoC;

TEST(ElfGameTest, TestFiveElves) {
    ASSERT_EQ(3, ElfGame::play(5));
}
