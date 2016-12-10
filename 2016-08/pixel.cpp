#include <gtest/gtest.h>

#include "pixel.h"

class PixelTest
	: public ::testing::Test {
protected:
	virtual void SetUp() override {

	}

	virtual void TearDown() override {

	}

	std::unique_ptr<PixelGrid> grid;
};

TEST_F(PixelTest, CanRunAStringCommand) {
	grid->runCommand("rect 1x1");
}

TEST_F(PixelTest, CanReturnALitPixelCount) {
	EXPECT_EQ(0, grid->litPixelCount());
}
