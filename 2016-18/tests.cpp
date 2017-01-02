#include <memory>
#include <sstream>
#include <gtest/gtest.h>

namespace AoC {
    class Tiler {
    public:
        static std::string nextRow(std::string row) {
            std::string result(row.length(), '.');
            for (int i = 0; i < row.length(); ++i) {
                bool left = isTrap(row, i - 1);
                bool center = isTrap(row, i);
                bool right = isTrap(row, i + 1);
                if (left && center && !right) {
                    result.at(i) = '^';
                } else if (center && right && !left) {
                    result.at(i) = '^';
                } else if (left && !center && !right) {
                    result.at(i) = '^';
                } else if (!left && !center && right) {
                    result.at(i) = '^';
                }
            }
            return result;
        }

        static bool isTrap(std::string row, int index) {
            if (index < 0) {
                return false;
            }
            if (index >= row.length()) {
                return false;
            }
            return '^' == row.at(index);
        }
    };
}

using namespace AoC;

TEST(TilerTest, NegativeIndexIsNotATrap) {
    ASSERT_FALSE(Tiler::isTrap("foo", -1));
}

TEST(TilerTest, OutOfRangeIndexIsNotATrap) {
    ASSERT_FALSE(Tiler::isTrap("foo", 3));
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
