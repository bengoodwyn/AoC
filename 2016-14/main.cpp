#include <iostream>
#include "KeyGenerator.h"

using namespace AoC;

int main(int argc, const char* argv[]) {
    bool part2 = (argc > 1 && argv[1][0] == '2');
    int keyStretching = part2 ? 2016 : 0;
    int desiredKeyIndex = 64;
    std::string salt = "zpqevtbw";
    KeyGenerator keyGenerator(salt, keyStretching);
    std::cout << keyGenerator.indexOfKey(desiredKeyIndex) << std::endl;
    return 0;
}
