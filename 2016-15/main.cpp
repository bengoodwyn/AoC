#include <fstream>
#include "Sculpture.h"

using namespace AoC;

int main(int argc, const char* argv[]) {
    bool part2 = (argc > 1 && argv[1][0] == '2');
    std::ifstream input("preprocessed-input");
    Sculpture sculpture(input);
    if (part2) {
        sculpture.addDisc(11, 0);
    }
    std::cout << sculpture.execute() << std::endl;
    return 0;
}
