#include <fstream>
#include "MicrochipFactory.h"

Bot::Comparator part1Comparator = [](int id, Value smaller, Value larger) -> bool {
    constexpr Value interestingSmaller{17};
    constexpr Value interestingLarger{61};
    if (smaller < larger) {
        if (smaller == interestingSmaller && larger == interestingLarger) {
            std::cout << id << std::endl;
        }
        return true;
    } else {
        if (larger == interestingSmaller && smaller == interestingLarger) {
            std::cout << id << std::endl;
        }
        return false;
    }
};

int main(int argc, const char* argv[]) {
    bool part2 = (argc > 1 && '2' == argv[1][0]);
    std::ifstream input("preprocessed-input");
    std::string line;
    MicrochipFactory factory{part2 ? Bot::DefaultComparator : part1Comparator};
    while (std::getline(input, line)) {
        factory.execute(line);
    }
    if (part2) {
        auto bin0 = factory.reproduceOutput(0);
        auto bin1 = factory.reproduceOutput(1);
        auto bin2 = factory.reproduceOutput(2);
        std::cout << bin0 * bin1 * bin2 << std::endl;
    }
    return 0;
}
