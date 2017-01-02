#include <memory>
#include <sstream>
#include <gtest/gtest.h>

#include "Tiler.h"

using namespace AoC;

TEST(TilerTest, NegativeIndexIsNotATrap) {
    ASSERT_FALSE(Tiler::isTrap("foo", -1));
}

TEST(TilerTest, OutOfRangeIndexIsNotATrap) {
    ASSERT_FALSE(Tiler::isTrap("foo", 3));
}

TEST(TilerTest, CanCountSafeTiles) {
    ASSERT_EQ(3, Tiler::countSafeTiles(".^.^."));
}

TEST(TilerTest, CaretIsATrap) {
    std::string row(".^.^.");
    ASSERT_FALSE(Tiler::isTrap(row, 0));
    ASSERT_TRUE(Tiler::isTrap(row, 1));
    ASSERT_FALSE(Tiler::isTrap(row, 2));
    ASSERT_TRUE(Tiler::isTrap(row, 3));
    ASSERT_FALSE(Tiler::isTrap(row, 4));
}

TEST(TilerTest, CanGetNextRow3x5) {
    std::string row("..^^.");
    std::string expectedRow(".^^^^");
    ASSERT_EQ(expectedRow, Tiler::nextRow(row));
    row = expectedRow;
    expectedRow = "^^..^";
    ASSERT_EQ(expectedRow, Tiler::nextRow(row));
}

TEST(TilerTest, CanGetNextRow10x10) {
    std::string row(".^^.^.^^^^");
    std::string expectedRow("^^^...^..^");
    ASSERT_EQ(expectedRow, Tiler::nextRow(row));
    row = expectedRow;
    expectedRow = "^.^^.^.^^.";
    ASSERT_EQ(expectedRow, Tiler::nextRow(row));
    row = expectedRow;
    expectedRow = "..^^...^^^";
    ASSERT_EQ(expectedRow, Tiler::nextRow(row));
    row = expectedRow;
    expectedRow = ".^^^^.^^.^";
    ASSERT_EQ(expectedRow, Tiler::nextRow(row));
    row = expectedRow;
    expectedRow = "^^..^.^^..";
    ASSERT_EQ(expectedRow, Tiler::nextRow(row));
    row = expectedRow;
    expectedRow = "^^^^..^^^.";
    ASSERT_EQ(expectedRow, Tiler::nextRow(row));
    row = expectedRow;
    expectedRow = "^..^^^^.^^";
    ASSERT_EQ(expectedRow, Tiler::nextRow(row));
    row = expectedRow;
    expectedRow = ".^^^..^.^^";
    ASSERT_EQ(expectedRow, Tiler::nextRow(row));
    row = expectedRow;
    expectedRow = "^^.^^^..^^";
    ASSERT_EQ(expectedRow, Tiler::nextRow(row));
}
