#include <fstream>
#include <iostream>
#include "Vm.h"

using namespace AoC;

int main(int argc, const char* argv[]) {
    //    bool part2 = (argc > 1 && argv[1][0] == '2');
    std::ifstream input("input");
    Vm vm;
    vm.load(input);
    vm.execute();
    std::cout << vm.read('a') << std::endl;
    return 0;
}
