#include <gtest/gtest.h>

#include "ValueReceiver.h"

class ValueTest : public ::testing::Test {
protected:
    virtual void SetUp() override {
        value.reset(new Value);
    }

    virtual void TearDown() override {
        value.reset(nullptr);
    }

    std::unique_ptr<Value> value;
};

TEST_F(ValueTest, CanSetAndGetAValue) {
    *value = 100;
    EXPECT_EQ(100, *value);
}

TEST_F(ValueTest, CanCompareTwoValues) {
    Value bigValue(200);
    Value smallValue(100);
    EXPECT_TRUE(smallValue < bigValue);
    EXPECT_FALSE(bigValue < smallValue);
}

