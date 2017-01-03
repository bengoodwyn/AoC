#pragma once

#include <iomanip>
#include <tuple>
#include <map>

namespace AoC {
    class Grid {
    public:
        using Id = std::pair<int, int>;
        using DiskUsage = std::pair<int, int>;

        void addNode(Id id, int used, int free) {
            maxX = std::max(maxX, id.first);
            maxY = std::max(maxY, id.second);
            grid[id] = {used, free};
        }

        int countViablePairs() {
            int count = 0;
            for (auto sourceNode : grid) {
                for (auto targetNode : grid) {
                    if ((sourceNode.second.first > 0) && (sourceNode.first != targetNode.first) &&
                        (sourceNode.second.first <= targetNode.second.second)) {
                        ++count;
                    }
                }
            }
            return count;
        }

        void printGrid() {
            for (int y = 0; y <= maxY; ++y) {
                for (int x = 0; x <= maxX; ++x) {
                    auto node = grid[{x, y}];
                    std::cout << std::setw(4) << node.first << std::setw(3) << node.second;
                }
                std::cout << std::endl;
            }
        }

    private:
        std::map<Id, DiskUsage> grid;
        int maxX{0};
        int maxY{0};
    };
}
