#include <memory>
#include <sstream>
#include <gtest/gtest.h>

#include <algorithm>
#include <string>

namespace AoC {
    class Scrambler {
    public:
        Scrambler(std::string input) : input(input) {
        }

        void scramble(std::string command) {
            std::stringstream stream(command);
            std::string commandClass;
            stream >> std::skipws >> commandClass;
            if ("swap" == commandClass) {
                scrambleSwap(stream);
            } else if ("reverse" == commandClass) {
                scrambleReverse(stream);
            } else if ("rotate" == commandClass) {
                scrambleRotate(stream);
            } else {
                assert(false);
            }
        }

        std::string result() {
            return input;
        }

    private:
        void scrambleReverse(std::istream& stream) {
            std::string junk;
            int firstIndex;
            int lastIndex;
            stream >> junk >> firstIndex >> junk >> lastIndex;
            auto start = std::next(input.begin(), firstIndex);
            auto end = std::next(input.begin(), lastIndex + 1);
            std::reverse(start, end);
        }

        void scrambleRotate(std::istream& stream) {
            std::string rotateType;
            stream >> rotateType;
            if ("left" == rotateType) {
                scrambleRotateLeft(stream);
            } else {
                assert(false);
            }
        }

        void scrambleRotateLeft(std::istream& stream) {
            int count;
            stream >> count;
            count = count % input.length();
            input = input.substr(count) + input.substr(0, count);
        }

        void scrambleSwap(std::istream& stream) {
            std::string swapType;
            stream >> swapType;
            if ("position" == swapType) {
                scrambleSwapPosition(stream);
            } else if ("letter" == swapType) {
                scrambleSwapLetter(stream);
            } else {
                assert(false);
            }
        }

        void scrambleSwapPosition(std::istream& stream) {
            int firstIndex;
            std::string junk;
            int secondIndex;
            stream >> firstIndex >> junk >> junk >> secondIndex;
            std::swap(input.at(firstIndex), input.at(secondIndex));
        }

        void scrambleSwapLetter(std::istream& stream) {
            char firstLetter;
            std::string junk;
            char secondLetter;
            stream >> firstLetter >> junk >> junk >> secondLetter;
            std::vector<int> firstLetterPositions;
            std::vector<int> secondLetterPositions;
            int pos = 0;
            for (auto letter : input) {
                if (letter == firstLetter) {
                    firstLetterPositions.push_back(pos);
                } else if (letter == secondLetter) {
                    secondLetterPositions.push_back(pos);
                }
                ++pos;
            }
            for (auto pos : firstLetterPositions) {
                input.at(pos) = secondLetter;
            }
            for (auto pos : secondLetterPositions) {
                input.at(pos) = firstLetter;
            }
        }

        std::string input;
    };
}

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
}
