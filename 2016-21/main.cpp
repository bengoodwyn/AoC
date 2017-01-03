#include <fstream>
#include <iostream>
#include <string>
#include "Scrambler.h"

using namespace AoC;

int main(int argc, const char* argv[]) {
    bool part2 = (argc > 1 && argv[1][0] == '2');
    if (part2) {
        std::ifstream inputCommands("input");
        std::vector<std::string> commands;
        while (!inputCommands.eof()) {
            std::string line;
            std::getline(inputCommands, line);
            if (line.length() > 0) {
                commands.push_back(line);
            }
        }
        std::reverse(commands.begin(), commands.end());
        const std::string inputString("fbgdceah");
        Scrambler scrambler(inputString);
        for (auto command : commands) {
            scrambler.unscramble(command);
        }
        std::cout << scrambler.result() << std::endl;
    } else {
        const std::string inputString("abcdefgh");
        std::ifstream inputCommands("input");
        Scrambler scrambler(inputString);
        while (!inputCommands.eof()) {
            std::string line;
            std::getline(inputCommands, line);
            if (line.length() > 0) {
                scrambler.scramble(line);
            }
        }
        std::cout << scrambler.result() << std::endl;
    }
    return 0;
}
