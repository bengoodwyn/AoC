#include <gtest/gtest.h>

#include "bots.h"

class OutputTest
	: public ::testing::Test {
protected:
	virtual void SetUp() override {
		output.reset(new Output);
	}

	virtual void TearDown() override {
		output.reset(nullptr);
	}

	std::unique_ptr<Output> output;
};

TEST_F(ValueTest, Nothing) {
}


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

class ValueTest
	: public ::testing::Test {
protected:
	virtual void SetUp() override {
		value.reset(new Value);
	}

	virtual void TearDown() override {
		value.reset(nullptr);
	}

	std::unique_ptr<Value> value;
};

TEST_F(ValueTest, Nothing) {
}

class FactoryTest
	: public ::testing::Test {
protected:
	virtual void SetUp() override {
		factory.reset(nullptr);
	}

	virtual void TearDown() override {
		factory.reset(nullptr);
	}

	std::unique_ptr<Factory> factory;
};

TEST_F(ValueTest, Nothing) {
}
