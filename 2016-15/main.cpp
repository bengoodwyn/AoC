#include <fstream>
#include "Sculpture.h"

using namespace AoC;

int main(int argc, const char* argv[]) {
    //bool part2 = (argc > 1 && argv[1][0] == '2');
    std::ifstream input("preprocessed-input");
    Sculpture sculpture(input);
    std::cout << sculpture.execute() << std::endl;
    return 0;
}
