#include <fstream>
#include <memory>
#include <sstream>
#include <gtest/gtest.h>

#include "Grid.h"

using namespace AoC;

class GridTest : public ::testing::Test {
public:
    virtual void SetUp() override {
        grid.reset(new Grid());
    }

    virtual void TearDown() override {
        grid.reset();
    }

    std::unique_ptr<Grid> grid;
};

TEST_F(GridTest, CanAddANodeToGrid) {
    grid->addNode({0, 0}, 1, 2);
}

TEST_F(GridTest, CanFindViablePairCountOfEmptyGrid) {
    ASSERT_EQ(0, grid->countViablePairs());
}

TEST_F(GridTest, CanFindViablePairCountOfASinglePair) {
    grid->addNode({0, 0}, 1, 999);
    grid->addNode({0, 1}, 1, 999);
    ASSERT_EQ(2, grid->countViablePairs());
}

TEST_F(GridTest, CanFindViablePairCountOfASinglePairWithAFatNode) {
    grid->addNode({0, 0}, 10, 999);
    grid->addNode({0, 1}, 10, 999);
    grid->addNode({1, 0}, 99999, 1);
    ASSERT_EQ(2, grid->countViablePairs());
}

TEST_F(GridTest, CanFindTheOneNodeWithRoomToStoreThisNode) {
    std::ifstream input("preprocessed-input");
    while (!input.eof()) {
        int x;
        int y;
        int used;
        int free;
        input >> std::skipws >> x >> y >> used >> free;
        grid->addNode({x, y}, used, free);
    }
    const auto expectedId = std::make_pair(13, 27);
    auto id = grid->findIdWithFreeSpaceFor({30, 0});
    ASSERT_EQ(expectedId, id);
}
