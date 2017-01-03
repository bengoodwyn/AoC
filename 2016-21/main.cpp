#include <fstream>
#include <iostream>
#include <string>
#include "Scrambler.h"

using namespace AoC;

int main(int argc, const char* argv[]) {
    // bool part2 = (argc > 1 && argv[1][0] == '2');
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
    return 0;
}
