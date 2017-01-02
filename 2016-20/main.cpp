#include <fstream>
#include <iostream>
#include <sstream>
#include "FirewallRules.h"

using namespace AoC;

int main(int argc, const char* argv[]) {
    bool part2 = (argc > 1 && argv[1][0] == '2');
    FirewallRules rules;
    std::ifstream input("input");
    while (input) {
        std::string line;
        std::getline(input, line);
        if (line.length() > 0) {
            line.at(line.find('-')) = ' ';
            std::stringstream stream(line);
            uint64_t start;
            uint64_t end;
            stream >> start >> end;
            rules.addRule(start, end);
        }
    }
    if (part2) {
        std::cout << rules.countUnblockedAddresses() << std::endl;
    } else {
        std::cout << rules.lowestUnblockedAddress() << std::endl;
    }
    return 0;
}
