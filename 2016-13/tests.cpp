#include <memory>
#include <sstream>
#include <gtest/gtest.h>

namespace AoC {
    class Maze {
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

TEST_F(MazeTest, Noop) {
}
