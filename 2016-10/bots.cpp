#include <gtest/gtest.h>

#include "bots.h"

class BotTest
	: public ::testing::Test {
protected:
	virtual void SetUp() override {
		bot.reset(new Bot);
	}

	virtual void TearDown() override {
		bot.reset(nullptr);
	}

	std::unique_ptr<Bot> bot;
};

TEST_F(BotTest, Nothing) {
}
