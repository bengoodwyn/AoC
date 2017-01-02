#pragma once

#include <string>

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

