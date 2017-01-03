#include <memory>
#include <sstream>
#include <gtest/gtest.h>

#include <tuple>
#include <map>

namespace AoC {
    class Grid {
    public:
        using Id = std::pair<int, int>;
        using DiskUsage = std::pair<unsigned int, unsigned int>;

        void addNode(Id id, int used, int free) {
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

    private:
        std::map<Id, DiskUsage> grid;
    };
}

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
