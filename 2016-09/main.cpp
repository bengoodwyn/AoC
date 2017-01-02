#include <fstream>
#include <iostream>
#include <sstream>
#include "decompress.h"

int main(int argc, const char* argv[]) {
    bool part2 = (argc > 1 && '2' == argv[1][0]);
    std::ifstream input("input");
    Decompressor decompressor;
    std::uint64_t decompressedLength = 0;
    std::uint64_t thisLength;
    while (0 != (thisLength = decompressor.run(input, part2))) {
        decompressedLength += thisLength;
    }
    std::cout << decompressedLength << std::endl;
    return 0;
}
