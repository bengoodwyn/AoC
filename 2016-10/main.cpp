#include <fstream>
#include "bots.h"

int main(int argc, const char* argv[]) {
    std::ifstream input("input");
    std::string line;
    Factory factory;
    while (std::getline(input, line)) {
        std::cout << line << std::endl;
        factory.execute(line);
    }
    Value bin0 = factory.reproduceOutput(0);
    Value bin1 = factory.reproduceOutput(1);
    Value bin2 = factory.reproduceOutput(2);
    std::cout << bin0 << " " << bin1 << " " << bin2 << " " << bin0 * bin1 * bin2 << std::endl;
    return 0;
}
