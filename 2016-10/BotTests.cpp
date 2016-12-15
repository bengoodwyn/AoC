#include <gtest/gtest.h>

#include "Bot.h"

class BotTest : public ::testing::Test {
protected:
    virtual void SetUp() override {
        bot.reset(new Bot{-1});
    }

    virtual void TearDown() override {
        bot.reset(nullptr);
    }

    std::unique_ptr<Bot> bot;
};

TEST_F(BotTest, HasAnId) {
    EXPECT_EQ(-1, bot->id);
}

TEST_F(BotTest, CanReceiveAValue) {
    Value value(100);
    bot->receive(value);
}
