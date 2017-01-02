#include <iostream>
#include "ElfGame.h"

using namespace AoC;

int main(int argc, const char* argv[]) {
    bool part2 = (argc > 1 && argv[1][0] == '2');
    const int count = 3005290;
    auto targetingFunction = part2 ? [](int index, int count) -> int {
        return (index + (count / 2)) % count;
    } : [](int index, int count) -> int {
        return (index + 1) % count;
    };
    std::cout << ElfGame::play(count, targetingFunction) << std::endl;
    return 0;
}
