#include <gtest/gtest.h>

#include "OutputBin.h"

class OutputBinTests : public ::testing::Test {
protected:
    virtual void SetUp() override {
        outputBin.reset(new OutputBin{-1});
    }

    virtual void TearDown() override {
        outputBin.reset(nullptr);
    }

    std::unique_ptr<OutputBin> outputBin;
};

TEST_F(OutputBinTests, CanReceiveAValue) {
    Value value(100);
    EXPECT_NO_THROW(outputBin->receive(value));
}

TEST_F(OutputBinTests, CanReproduceAReceivedValue) {
    Value value(100);
    outputBin->receive(value);
    EXPECT_EQ(100, outputBin->reproduce());
}

