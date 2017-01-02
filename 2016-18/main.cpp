#include <iostream>
#include "Tiler.h"

using namespace AoC;

int main(int argc, const char* argv[]) {
    bool part2 = (argc > 1 && argv[1][0] == '2');
    const std::string inputRow
        ("^.....^.^^^^^.^..^^.^.......^^..^^^..^^^^..^.^^.^.^....^^...^^.^^.^...^^.^^^^..^^.....^.^...^.^.^^.^");
    const int rows = part2 ? 400000 : 40;
    int safeTiles = Tiler::countSafeTiles(inputRow);
    std::string currentRow = inputRow;
    for (int i = 1; i < rows; ++i) {
        currentRow = Tiler::nextRow(currentRow);
        safeTiles += Tiler::countSafeTiles(currentRow);
    }
    std::cout << safeTiles << std::endl;
    return 0;
}
