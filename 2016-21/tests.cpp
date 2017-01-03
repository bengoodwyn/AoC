#include <memory>
#include <sstream>
#include <gtest/gtest.h>

#include "Scrambler.h"

using namespace AoC;

TEST(ScramblerTest, CanRunTheSampleTransormations) {
    Scrambler scrambler("abcde");
    scrambler.scramble("swap position 4 with position 0");
    ASSERT_EQ("ebcda", scrambler.result());
    scrambler.scramble("swap letter d with letter b");
    ASSERT_EQ("edcba", scrambler.result());
    scrambler.scramble("reverse positions 0 through 4");
    ASSERT_EQ("abcde", scrambler.result());
    scrambler.scramble("rotate left 1 step");
    ASSERT_EQ("bcdea", scrambler.result());
    scrambler.scramble("move position 1 to position 4");
    ASSERT_EQ("bdeac", scrambler.result());
    scrambler.scramble("move position 3 to position 0");
    ASSERT_EQ("abdec", scrambler.result());
    scrambler.scramble("rotate based on position of letter b");
    ASSERT_EQ("ecabd", scrambler.result());
    scrambler.scramble("rotate based on position of letter d");
    ASSERT_EQ("decab", scrambler.result());
}

TEST(ScramblerTest, CanRotateRight) {
    Scrambler scrambler("abcde");
    scrambler.scramble("rotate right 1 step");
    ASSERT_EQ("eabcd", scrambler.result());
}
