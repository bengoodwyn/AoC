#include <fstream>
#include <iostream>
#include "Grid.h"

using namespace AoC;

int main(int argc, const char* argv[]) {
    bool part2 = (argc > 1 && argv[1][0] == '2');
    Grid grid;
    std::ifstream input("preprocessed-input");
    while (!input.eof()) {
        int x;
        int y;
        int used;
        int free;
        input >> std::skipws >> x >> y >> used >> free;
        grid.addNode({x, y}, used, free);
    }
    if (part2) {
        grid.printGrid();
    } else {
        std::cout << grid.countViablePairs() << std::endl;
    }
    return 0;
}
