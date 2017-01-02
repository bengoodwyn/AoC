#include <iostream>
#include "Dragon.h"

using namespace AoC;

int main(int argc, const char* argv[]) {
    bool part2 = (argc > 1 && argv[1][0] == '2');
    std::string datum = Dragon::generate("11101000110010100", part2 ? 35651584 : 272);
    std::string checksum = Dragon::checksum(datum);
    std::cout << checksum << std::endl;
    return 0;
}
