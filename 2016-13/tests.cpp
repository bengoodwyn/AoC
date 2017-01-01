#include <memory>
#include <sstream>
#include <gtest/gtest.h>

#include <functional>
#include <tuple>

namespace AoC {
    class Maze {
    public:
        using Point = std::pair<int, int>;
        using WallAlgorithm = std::function<bool(Point)>;

        Maze(WallAlgorithm wallAlgorithm) : wallAlgorithm(wallAlgorithm) {
        }

        bool isWall(Point point) const {
            return false;
        }

        int distanceTo(Point point) const {
            return point.first + point.second;
        }

    private:
        const WallAlgorithm wallAlgorithm;
    };
}

using namespace AoC;

class MazeTest : public ::testing::Test {
public:
    Maze::WallAlgorithm openMazeWallAlgorithm = [](Maze::Point point) -> bool {
        return false;
    };

    virtual void SetUp() override {
        maze.reset(new Maze(openMazeWallAlgorithm));
    }

    virtual void TearDown() override {
        maze.reset();
    }

    std::unique_ptr<Maze> maze;
};

TEST_F(MazeTest, OriginIsNotAWall) {
    ASSERT_FALSE(maze->isWall({0, 0}));
}

TEST_F(MazeTest, CanGetMinimumMovesToOrigin) {
    ASSERT_EQ(0, maze->distanceTo({0, 0}));
}

TEST_F(MazeTest, DistanceToNeighborOfOriginIs1) {
    ASSERT_EQ(1, maze->distanceTo({1, 0}));
}
