#include <list>
#include <memory>
#include <gtest/gtest.h>
#include "Traveler.h"

using namespace AoC;

class TravelerTest : public ::testing::Test, public Traveler::Follower {
public:
    virtual void SetUp() override {
        traveler.reset(new Traveler);
        traveler->addFollower(*this);
    }

    virtual void TearDown() override {
        traveler.reset(nullptr);
        positions.clear();
    }

    virtual void onTravelerMoved(Traveler& traveler) override {
        positions.push_back(traveler.currentPosition());
    }

    std::unique_ptr<Traveler> traveler;
    std::list<Traveler::Position> positions;
};

TEST_F(TravelerTest, CanGetDefaultPosition) {
    auto position = traveler->currentPosition();
    EXPECT_EQ(0, position.first);
    EXPECT_EQ(0, position.second);
}

TEST_F(TravelerTest, CanGetDefaultDirection) {
    EXPECT_EQ(Facing::North, traveler->currentFacing());
}

TEST_F(TravelerTest, CanTurnToTheRight) {
    traveler->turn(Turn::Right);
    EXPECT_EQ(Facing::East, traveler->currentFacing());
}

TEST_F(TravelerTest, CanTurnToTheLeft) {
    traveler->turn(Turn::Left);
    EXPECT_EQ(Facing::West, traveler->currentFacing());
}

TEST_F(TravelerTest, CanTravelNorth) {
    traveler->travel(17);
    auto position = traveler->currentPosition();
    EXPECT_EQ(0, position.first);
    EXPECT_EQ(17, position.second);
}

TEST_F(TravelerTest, CanTravelEast) {
    traveler->turn(Turn::Right);
    traveler->travel(19);
    auto position = traveler->currentPosition();
    EXPECT_EQ(19, position.first);
    EXPECT_EQ(0, position.second);
}

TEST_F(TravelerTest, CanTravelWest) {
    traveler->turn(Turn::Left);
    traveler->travel(13);
    auto position = traveler->currentPosition();
    EXPECT_EQ(-13, position.first);
    EXPECT_EQ(0, position.second);
}

TEST_F(TravelerTest, CanTravelSouth) {
    traveler->turn(Turn::Left);
    traveler->turn(Turn::Left);
    traveler->travel(7);
    auto position = traveler->currentPosition();
    EXPECT_EQ(0, position.first);
    EXPECT_EQ(-7, position.second);
}

TEST_F(TravelerTest, CanTravelSouthThenWest) {
    traveler->turn(Turn::Left);
    traveler->turn(Turn::Left);
    traveler->travel(7);
    traveler->turn(Turn::Right);
    traveler->travel(11);
    auto position = traveler->currentPosition();
    EXPECT_EQ(-11, position.first);
    EXPECT_EQ(-7, position.second);
}

TEST_F(TravelerTest, CanGetShortestPathDistanceFromOrigin) {
    traveler->turn(Turn::Left);
    traveler->turn(Turn::Left);
    traveler->travel(7);
    traveler->turn(Turn::Right);
    traveler->travel(11);
    traveler->turn(Turn::Right);
    traveler->travel(3);
    auto distance = traveler->distanceFromOrigin();
    EXPECT_EQ(15, distance);
}

TEST_F(TravelerTest, ReportsPositionChangesToTheFollower) {
    traveler->travel(1);
    EXPECT_EQ(1, positions.size());
    EXPECT_EQ(positions.front(), traveler->currentPosition());
    traveler->turn(Turn::Right);
    traveler->travel(1);
    EXPECT_EQ(2, positions.size());
    EXPECT_EQ(positions.back(), traveler->currentPosition());
    EXPECT_NE(positions.front(), positions.back());
}
