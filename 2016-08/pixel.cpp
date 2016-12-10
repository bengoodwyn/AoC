#include <gtest/gtest.h>

#include "pixel.h"

class PixelTest
	: public ::testing::Test {
protected:
	static constexpr int TEST_WIDTH = 50;
	static constexpr int TEST_HEIGHT = 6;

	virtual void SetUp() override {
		grid.reset(new PixelGrid(50, 6));
	}

	virtual void TearDown() override {
		grid.reset(nullptr);
	}

	std::unique_ptr<PixelGrid> grid;
};

TEST_F(PixelTest, CanRunAStringCommand) {
	grid->runCommand("rect 1x1");
}

TEST_F(PixelTest, CanReturnALitPixelCount) {
	EXPECT_EQ(0, grid->litPixelCount());
}
