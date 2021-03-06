#pragma once

#include <algorithm>
#include <cassert>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace AoC {
    class Scrambler;

    class Scrambler {
    public:
        Scrambler(std::string input) : input(input) {
        }

        void unscramble(std::string command) {
            std::stringstream stream(command);
            std::string commandClass;
            stream >> std::skipws >> commandClass;
            if ("swap" == commandClass) {
                scrambleSwap(stream);
            } else if ("reverse" == commandClass) {
                scrambleReverse(stream);
            } else if ("rotate" == commandClass) {
                scrambleUnrotate(stream);
            } else if ("move" == commandClass) {
                scrambleUnmove(stream);
            } else {
                assert(false);
            }
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
            } else if ("move" == commandClass) {
                scrambleMove(stream);
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

        void scrambleUnmove(std::istream& stream) {
            std::string junk;
            int removeIndex;
            int insertIndex;
            stream >> junk >> insertIndex >> junk >> junk >> removeIndex;
            auto character = input.at(removeIndex);
            input.erase(removeIndex, 1);
            input.insert(insertIndex, 1, character);
        }

        void scrambleMove(std::istream& stream) {
            std::string junk;
            int removeIndex;
            int insertIndex;
            stream >> junk >> removeIndex >> junk >> junk >> insertIndex;
            auto character = input.at(removeIndex);
            input.erase(removeIndex, 1);
            input.insert(insertIndex, 1, character);
        }

        void scrambleRotate(std::istream& stream) {
            std::string rotateType;
            stream >> rotateType;
            if ("left" == rotateType) {
                scrambleRotateLeft(stream);
            } else if ("right" == rotateType) {
                scrambleRotateRight(stream);
            } else if ("based" == rotateType) {
                scrambleRotateBased(stream);
            } else {
                assert(false);
            }
        }

        void scrambleUnrotate(std::istream& stream) {
            std::string rotateType;
            stream >> rotateType;
            if ("left" == rotateType) {
                scrambleRotateRight(stream);
            } else if ("right" == rotateType) {
                scrambleRotateLeft(stream);
            } else if ("based" == rotateType) {
                scrambleUnrotateBased(stream);
            } else {
                assert(false);
            }
        }

        void scrambleUnrotateBased(std::istream& stream) {
            std::string junk;
            char letter;
            stream >> junk >> junk >> junk >> junk >> letter;
            // Rotate to the left until it is right
            std::unique_ptr<Scrambler> scrambler;
            int leftShift = 1;
            while (true) {
                std::string unrotated = input.substr(leftShift) + input.substr(0, leftShift);
                scrambler.reset(new Scrambler(unrotated));
                scrambler->scramble(std::string("rotate based on position of letter ") + letter);
                if (scrambler->result() == input) {
                    input = unrotated;
                    return;
                }
                ++leftShift;
            }
        }

        void scrambleRotateBased(std::istream& stream) {
            std::string junk;
            char letter;
            stream >> junk >> junk >> junk >> junk >> letter;
            auto pos = input.find(letter);
            int rotates = 1 + pos + ((pos >= 4) ? 1 : 0);
            rotates = input.length() - (rotates % input.length());
            input = input.substr(rotates) + input.substr(0, rotates);
        }

        void scrambleRotateLeft(std::istream& stream) {
            int count;
            stream >> count;
            count = count % input.length();
            input = input.substr(count) + input.substr(0, count);
        }

        void scrambleRotateRight(std::istream& stream) {
            int count;
            stream >> count;
            count = input.length() - (count % input.length());
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

