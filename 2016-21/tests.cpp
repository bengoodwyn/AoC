#include <memory>
#include <sstream>
#include <gtest/gtest.h>

#include <string>

namespace AoC {
    class Scrambler {
    public:
        Scrambler(std::string input) : input(input) {
        }

        void scramble(std::string command) {
            std::stringstream stream(command);
            std::string commandClass;
            stream >> commandClass;
            if ("swap" == commandClass) {
                scrambleSwap(stream);
            } else {
                assert(false);
            }
        }

        std::string result() {
            return input;
        }

    private:
        void scrambleSwap(std::istream& stream) {
            std::string swapType;
            stream >> swapType;
            if ("position" == swapType) {
                scrambleSwapPosition(stream);
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

        std::string input;
    };
}

using namespace AoC;

TEST(ScramblerTest, CanRunTheSampleTransormations) {
    Scrambler scrambler("abcde");
    scrambler.scramble("swap position 4 with position 0");
    ASSERT_EQ("ebcda", scrambler.result());
}
