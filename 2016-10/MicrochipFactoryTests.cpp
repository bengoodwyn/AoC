#include <gtest/gtest.h>

#include "MicrochipFactory.h"

class MicrochipFactoryTest : public ::testing::Test {
protected:
    virtual void SetUp() override {
        factory.reset(new MicrochipFactory);
    }

    virtual void TearDown() override {
        factory.reset(nullptr);
    }

    std::unique_ptr<MicrochipFactory> factory;
};

TEST_F(MicrochipFactoryTest, RejectsABadCommand) {
    EXPECT_THROW(factory->execute("bad command"), MicrochipFactory::BadCommand);
}

TEST_F(MicrochipFactoryTest, CanReproduceItemsSentToOutputBins) {
    factory->execute("value 100 bot 1");
    factory->execute("value 200 bot 1");
    factory->execute("value 3000 bot 2");
    factory->execute("value 4000 bot 3");
    factory->execute("bot 1 output 2 output 3");
    EXPECT_EQ(100, factory->reproduceOutput(2));
    EXPECT_EQ(200, factory->reproduceOutput(3));
}
