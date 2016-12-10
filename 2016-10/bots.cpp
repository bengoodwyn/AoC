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

TEST_F(OutputTest, CanReceiveAValue) {
	Value value(100);
	output->receive(value);
}

TEST_F(OutputTest, CanReproduceAReceivedValue) {
	Value value(100);
	output->receive(value);
	EXPECT_EQ(100, output->reproduce());
}

class BotTest
	: public ::testing::Test, public Bot::Listener {
protected:
	virtual void SetUp() override {
		bot.reset(new Bot{-1, *this});
	}

	virtual void TearDown() override {
		bot.reset(nullptr);
		onFullCalled = false;
	}

	virtual void OnBotFull(Bot& fullBot) override {
		onFullCalled = true;
	}

	std::unique_ptr<Bot> bot;
	bool onFullCalled{false};
};

TEST_F(BotTest, HasAnId) {
	EXPECT_EQ(-1, bot->id);
}

TEST_F(BotTest, HasAValueCount) {
	EXPECT_EQ(0, bot->valueCount());
}

TEST_F(BotTest, CanReceiveAValue) {
	Value value(100);
	bot->receive(value);
}

TEST_F(BotTest, doesntCallOnFullWithOneValue) {
	Value value1(100);
	bot->receive(value1);
	EXPECT_FALSE(onFullCalled);
}

TEST_F(BotTest, CallsOnFullWithTwoValues) {
	Value value1(100);
	Value value2(200);
	bot->receive(value1);
	bot->receive(value2);
	EXPECT_TRUE(onFullCalled);
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

TEST_F(BotTest, CanTakeTwoValuesUsingHigh) {
	Value value1(50);
	Value value2(60);
	bot->receive(value1);
	bot->receive(value2);
	EXPECT_EQ(60, bot->takeHighValue());
	EXPECT_EQ(50, bot->takeHighValue());
}

TEST_F(BotTest, CanTakeTwoValuesInReverseOrderUsingHigh) {
	Value value1(60);
	Value value2(50);
	bot->receive(value1);
	bot->receive(value2);
	EXPECT_EQ(60, bot->takeHighValue());
	EXPECT_EQ(50, bot->takeHighValue());
}

TEST_F(BotTest, CanGiveLowValueToAnotherBot) {
	Bot otherBot{-2, *this};
	Value lowValue(127);
	Value highValue(9999);
	bot->receive(lowValue);
	bot->receive(highValue);
	bot->giveLowValueTo(otherBot);
	EXPECT_EQ(lowValue, otherBot.takeLowValue());
}

TEST_F(BotTest, CanGiveHighValueToAnotherBot) {
	Bot otherBot{-3, *this};
	Value lowValue(127);
	Value highValue(9999);
	bot->receive(lowValue);
	bot->receive(highValue);
	bot->giveHighValueTo(otherBot);
	EXPECT_EQ(highValue, otherBot.takeHighValue());
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
		factory.reset(new Factory);
	}

	virtual void TearDown() override {
		factory.reset(nullptr);
	}

	std::unique_ptr<Factory> factory;
};

TEST_F(FactoryTest, RejectsABadCommand) {
	EXPECT_THROW(factory->execute("bad command"), Factory::BadCommand);
}

TEST_F(FactoryTest, CanGiveValuesToABotAndGetThemBack) {
	factory->execute("value 5 goes to bot 2");
	factory->execute("value 100 goes to bot 2");
	EXPECT_EQ(5, factory->bot(2).takeLowValue());
	EXPECT_EQ(100, factory->bot(2).takeLowValue());
}

TEST_F(FactoryTest, CanGiveValuesToDifferentBotsAndGetThemBack) {
	factory->execute("value 5 goes to bot 2");
	factory->execute("value 100 goes to bot 20");
	EXPECT_EQ(100, factory->bot(20).takeLowValue());
	EXPECT_EQ(5, factory->bot(2).takeLowValue());
}

TEST_F(FactoryTest, CanTellABotWhatToDo) {
	factory->execute("value 100 goes to bot 1");
	factory->execute("value 200 goes to bot 1");
	factory->execute("bot 1 gives low to bot 2 and high to bot 3");
	EXPECT_EQ(100, factory->bot(2).takeLowValue());
	EXPECT_EQ(200, factory->bot(3).takeLowValue());
}

TEST_F(FactoryTest, CanPutItemsInAnOutputBin) {
	factory->execute("value 100 goes to bot 1");
	factory->execute("value 200 goes to bot 1");
	factory->execute("value 3000 goes to bot 2");
	factory->execute("value 4000 goes to bot 3");
	factory->execute("bot 1 gives low to output 2 and high to output 3");
	EXPECT_EQ(3000, factory->bot(2).takeLowValue());
	EXPECT_EQ(4000, factory->bot(3).takeLowValue());
}

TEST_F(FactoryTest, CanTellABotWhatToDoBeforeYouGiveItAnyValues) {
	factory->execute("bot 1 gives low to bot 2 and high to bot 3");
	factory->execute("value 100 goes to bot 1");
	factory->execute("value 200 goes to bot 1");
	EXPECT_EQ(100, factory->bot(2).takeLowValue());
	EXPECT_EQ(200, factory->bot(3).takeLowValue());
}

TEST_F(FactoryTest, CanReproduceItemsSentToOutputBins) {
	factory->execute("value 100 goes to bot 1");
	factory->execute("value 200 goes to bot 1");
	factory->execute("value 3000 goes to bot 2");
	factory->execute("value 4000 goes to bot 3");
	factory->execute("bot 1 gives low to output 2 and high to output 3");
	EXPECT_EQ(100, factory->reproduceOutput(2));
	EXPECT_EQ(200, factory->reproduceOutput(3));
}
