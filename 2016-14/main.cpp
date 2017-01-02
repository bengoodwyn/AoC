#include <iostream>
#include "KeyGenerator.h"

using namespace AoC;

int main(int argc, const char* argv[]) {
    int desiredKeyIndex = 64;
    std::string salt = "zpqevtbw";
    KeyGenerator keyGenerator(salt);
    std::cout << keyGenerator.indexOfKey(desiredKeyIndex) << std::endl;
    return 0;
}
