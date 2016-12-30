#include <memory>
#include <sstream>
#include <gtest/gtest.h>

#include <tuple>

namespace AoC {
    class Maze {
    public:
        using Point = std::pair<int, int>;

        bool isWall(Point point) const {
            return false;
        }
    };
}

using namespace AoC;

class MazeTest : public ::testing::Test {
public:
    virtual void SetUp() override {
        maze.reset();
    }

    virtual void TearDown() override {
        maze.reset();
    }

    std::unique_ptr<Maze> maze;
};

TEST_F(MazeTest, OriginIsNotAWall) {
    ASSERT_FALSE(maze->isWall({0, 0}));
}
