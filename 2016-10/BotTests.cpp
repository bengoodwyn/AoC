#include <gtest/gtest.h>

#include "Bot.h"

class TestReceiver : public ValueReceiver {
public:
    TestReceiver() : ValueReceiver{-1} {
    }

    virtual void receive(Value value) override {
        received = value;
    }

    Value received;
};

class BotTest : public ::testing::Test {
protected:
    virtual void SetUp() override {
        id = 0;
        low = 0;
        high = 0;
        bot.reset(new Bot{-1, [this](int botid, Value a, Value b) -> bool {
            id = botid;
            low = std::min(a, b);
            high = std::max(a, b);
            return Bot::DefaultComparator(botid, a, b);
        }});
        lowReceiver.reset(new TestReceiver);
        highReceiver.reset(new TestReceiver);
    }

    virtual void TearDown() override {
        bot.reset(nullptr);
        lowReceiver.reset(nullptr);
        highReceiver.reset(nullptr);
    }

    int id;
    Value low;
    Value high;
    std::unique_ptr<Bot> bot;
    std::unique_ptr<TestReceiver> lowReceiver;
    std::unique_ptr<TestReceiver> highReceiver;
};

TEST_F(BotTest, HasAnId) {
    EXPECT_EQ(-1, bot->id);
}

TEST_F(BotTest, CanReceiveAValue) {
    Value value(100);
    EXPECT_NO_THROW(bot->receive(value));
}

TEST_F(BotTest, CanBeConnectedAndEmitsReceivedValues) {
    bot->connectTo(lowReceiver.get(), highReceiver.get());
    bot->receive(7);
    bot->receive(8);
    EXPECT_EQ(7, lowReceiver->received);
    EXPECT_EQ(8, highReceiver->received);
}

TEST_F(BotTest, CanBeConnectedAndEmitsReceivedValuesInReverseOrder) {
    bot->receive(7);
    bot->receive(8);
    bot->connectTo(lowReceiver.get(), highReceiver.get());
    EXPECT_EQ(7, lowReceiver->received);
    EXPECT_EQ(8, highReceiver->received);
}

TEST_F(BotTest, CallsACustomComparator) {
    bot->receive(7);
    bot->receive(8);
    bot->connectTo(lowReceiver.get(), highReceiver.get());
    EXPECT_EQ(-1, id);
    EXPECT_EQ(7, low);
    EXPECT_EQ(8, high);
}
