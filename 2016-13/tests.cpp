#include <memory>
#include <sstream>
#include <gtest/gtest.h>
#include "Maze.h"

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
    ASSERT_FALSE(maze->isWall({1, 1}));
}

TEST_F(MazeTest, CanGetMinimumMovesToOrigin) {
    ASSERT_EQ(0, maze->distanceTo({1, 1}));
}

TEST_F(MazeTest, DistanceToNeighborOfOriginIs1) {
    ASSERT_EQ(1, maze->distanceTo({1, 0}));
}

TEST_F(MazeTest, AskingIsWallGetsResultFromAlgorithm) {
    Maze::Point calledWith;
    bool nextResult = false;
    Maze::WallAlgorithm algo = [&calledWith, &nextResult](Maze::Point point) -> bool {
        calledWith = point;
        return nextResult;
    };
    maze.reset(new Maze(algo));
    nextResult = true;
    ASSERT_TRUE(maze->isWall(Maze::Point(17, 14)));
    ASSERT_EQ(Maze::Point(17, 14), calledWith);
    nextResult = false;
    ASSERT_FALSE(maze->isWall(Maze::Point(97, 99)));
    ASSERT_EQ(Maze::Point(97, 99), calledWith);
}
