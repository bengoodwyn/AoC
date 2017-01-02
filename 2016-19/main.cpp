#include <iostream>
#include "ElfGame.h"

using namespace AoC;

int main(int argc, const char* argv[]) {
    // bool part2 = (argc > 1 && argv[1][0] == '2');
    const int count = 3005290;
    std::cout << ElfGame::play(count) << std::endl;
    return 0;
}
