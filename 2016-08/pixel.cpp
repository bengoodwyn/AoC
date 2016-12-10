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

TEST_F(PixelTest, CreatingA1x1RectLights1Pixel) {
	grid->runCommand("rect 1x1");
	EXPECT_EQ(1, grid->litPixelCount());
}

TEST_F(PixelTest, CanLightAllPixels) {
	grid->runCommand(
		std::string("rect ") + std::to_string(TEST_WIDTH) + std::string("x") + std::to_string(TEST_HEIGHT));
	EXPECT_EQ(TEST_WIDTH * TEST_HEIGHT, grid->litPixelCount());
}

TEST_F(PixelTest, NoPixelsLitByDefault) {
	EXPECT_EQ(0, grid->litPixelCount());
}

TEST_F(PixelTest, OverwritingAPixelIsNotCountedAsLit) {
	grid->runCommand("rect 1x1");
	grid->runCommand("rect 1x1");
	EXPECT_EQ(1, grid->litPixelCount());
}
