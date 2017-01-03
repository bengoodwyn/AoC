#include <memory>
#include <sstream>
#include <gtest/gtest.h>

#include <tuple>

namespace AoC {
    class Grid {
    public:
        using Id = std::pair<int, int>;

        void addNode(Id id, int used, int free) {

        }
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
