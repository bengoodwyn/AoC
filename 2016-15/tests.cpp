#include <memory>
#include <sstream>
#include <gtest/gtest.h>

class Test : public ::testing::Test {
public:
    virtual void SetUp() override {
    }

    virtual void TearDown() override {
    }
};

TEST_F(Test, Noop) {
    ASSERT_TRUE(true);
}
