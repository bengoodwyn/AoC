#include <gtest/gtest.h>

class TestCase : public ::testing::Test {
public:
    virtual void SetUp() override {
    }

    virtual void TearDown() override {
    }
};

TEST_F(TestCase, Template) {
    ASSERT_TRUE(true);
}
