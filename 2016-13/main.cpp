#include <iostream>
#include "Maze.h"

using namespace AoC;

int main(int argc, const char* argv[]) {
    //bool part2 = (argc > 1 && argv[1][0] == '2');
    const Maze::Point destination{31, 39};
    const int input = 1362;
    auto isWall = [input](Maze::Point point) -> bool {
        auto& x = point.first;
        auto& y = point.second;
        auto value = x * x + 3 * x + 2 * x * y + y + y * y;
        value += input;
        auto bits = __builtin_popcount(value);
        return (0x1 == (bits & 0x1));
    };
    Maze maze{isWall};
    std::cout << maze.distanceTo(destination) << std::endl;
    return 0;
}
