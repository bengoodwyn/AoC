#include <memory>
#include <sstream>
#include <gtest/gtest.h>

#include "Sculpture.h"

using namespace AoC;

class SculptureTest : public ::testing::Test {
public:
    virtual void SetUp() override {
        std::stringstream stream("5 4\n2 1\n");
        sculpture.reset(new Sculpture(stream));
    }

    virtual void TearDown() override {
        sculpture.reset();
    }

    std::unique_ptr<Sculpture> sculpture;
};

TEST_F(SculptureTest, CanFindTimeToDropDisc) {
    ASSERT_EQ(5, sculpture->execute());
}
