#include <fstream>
#include <iostream>

#include "Facility.h"

using namespace AoC;

int main(int argc, const char* argv[]) {
    std::ifstream input("preprocessed-input");
    std::string line;
    Facility facility;
    while (std::getline(input, line)) {
        facility.addFloor(line);
    }
    return 0;
}
