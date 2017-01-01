#include <cassert>
#include <functional>
#include <set>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace AoC {
    class Maze {
    public:
        using Point = std::pair<int, int>;
        using WallAlgorithm = std::function<bool(Point)>;

        Maze(WallAlgorithm wallAlgorithm) : wallAlgorithm{wallAlgorithm} {
            reachablePointsByDistance[0].insert({1, 1});
            visitedPoints.insert({1, 1});
        }

        bool isWall(Point point) {
            return wallAlgorithm(point);
        }

        int distanceTo(Point point) {
            int distance = 0;
            assert(!isWall(point));
            assert(point.first >= 0 && point.second >= 0);
            while (true) {
                auto& reachablePoints = reachablePointsByDistance[distance];

                if (reachablePoints.empty()) {
                    std::cerr << "Exploring distance " << distance << std::endl;
                    explore(distance);
                }

                if (reachablePoints.end() != reachablePoints.find(point)) {
                    return distance;
                }

                ++distance;
            }
        }

    private:
        void explore(int distance) {
            for (auto point : reachablePointsByDistance[distance - 1]) {
                explore({point.first - 1, point.second}, distance);
                explore({point.first, point.second - 1}, distance);
                explore({point.first + 1, point.second}, distance);
                explore({point.first, point.second + 1}, distance);
            }
        }

        void explore(Point point, int distance) {
            if (point.first < 0 || point.second < 0) {
                return;
            }

            if (isWall(point)) {
                return;
            }

            if (visitedPoints.end() != visitedPoints.find(point)) {
                return;
            }

            reachablePointsByDistance[distance].insert(point);
            visitedPoints.insert(point);
        }

        const WallAlgorithm wallAlgorithm;
        std::unordered_map<int, std::set<Point>> reachablePointsByDistance;
        std::set<Point> visitedPoints;
    };
}

