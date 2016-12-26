#include <fstream>
#include <iostream>
#include <unordered_map>
#include "Facility.h"

using namespace AoC;

int main(int argc, const char* argv[]) {
    bool part2 = (argc > 1 && '2' == argv[1][0]);
    std::unordered_map<std::string, int> exploredMoves;
    std::vector<std::vector<Facility>> facilities;

    std::ifstream input("preprocessed-input");
    Facility rootFacility;
    rootFacility.serialize(input);

    if (part2) {
        rootFacility.addItem(1, new GeneratorItem{"elerium"});
        rootFacility.addItem(1, new MicrochipItem{"elerium"});
        rootFacility.addItem(1, new GeneratorItem{"dilithium"});
        rootFacility.addItem(1, new MicrochipItem{"dilithium"});
        assert(rootFacility.isLegal());
    }

    int cycles = 0;
    int moveDepth = 0;
    facilities.resize(moveDepth + 1);
    facilities[moveDepth].push_back(rootFacility);
    exploredMoves[rootFacility.serialize()] = moveDepth;

    while (facilities[moveDepth].size() > 0) {
        ++moveDepth;
        std::cerr << "Searching move depth " << moveDepth << std::endl;
        facilities.resize(moveDepth + 1);
        for (const auto& facility : facilities[moveDepth - 1]) {
            for (const auto& move : facility.moves()) {
                std::string serializedMove = move.serialize();
                if (exploredMoves.end() == exploredMoves.find(serializedMove)) {
                    exploredMoves[serializedMove] = moveDepth;
                    facilities[moveDepth].push_back(move);
                    if (move.isEndingMove()) {
                        std::cout << moveDepth << std::endl;
                        return 0;
                    }
                } else {
                    ++cycles;
                }
            }
        }
    }
    std::cerr << "ERROR: No useful moves found after exploring depth " << moveDepth << std::endl;
    return 1;
}
