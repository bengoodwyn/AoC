#include <iostream>
#include "ShortestPath.h"

using namespace AoC;

int main(int argc, const char* argv[]) {
    bool part2 = (argc > 1 && argv[1][0] == '2');
    if (part2) {
        std::cout << ShortestPath::find("pgflpeqp", ShortestPath::PathType::Longest).length() << std::endl;
    } else {
        std::cout << ShortestPath::find("pgflpeqp") << std::endl;
    }
    return 0;
}
