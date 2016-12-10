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

TEST_F(OutputTest, Nothing) {
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

TEST_F(BotTest, CanReceiveAValue) {
	Value value(100);
	bot->receive(value);
}

TEST_F(BotTest, CanTakeHighValue) {
	Value value1(100);
	Value value2(200);
	bot->receive(value1);
	bot->receive(value2);
	EXPECT_EQ(200, bot->takeHighValue());
}

TEST_F(BotTest, CanTakeLowValue) {
	Value value1(100);
	Value value2(200);
	bot->receive(value1);
	bot->receive(value2);
	EXPECT_EQ(100, bot->takeLowValue());
}

TEST_F(BotTest, CanTakeTwoValues) {
	Value value1(50);
	Value value2(60);
	bot->receive(value1);
	bot->receive(value2);
	EXPECT_EQ(50, bot->takeLowValue());
	EXPECT_EQ(60, bot->takeLowValue());
}

TEST_F(BotTest, CanTakeTwoValuesInReverseOrder) {
	Value value1(60);
	Value value2(50);
	bot->receive(value1);
	bot->receive(value2);
	EXPECT_EQ(50, bot->takeLowValue());
	EXPECT_EQ(60, bot->takeLowValue());
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

TEST_F(FactoryTest, Nothing) {
}
