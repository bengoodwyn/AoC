#include <fstream>
#include <iostream>
#include <sstream>
#include "decompress.h"

int main(int argc, const char* argv[]) {
    std::ifstream input("input");
    std::ofstream output("/dev/null");
    Decompressor decompressor;
    std::uint64_t decompressedLength = 0;
    std::uint64_t thisLength;
    while (0 != (thisLength = decompressor.run(input, output))) {
        decompressedLength += thisLength;
    }
    std::cout << decompressedLength << std::endl;
    return 0;
}
