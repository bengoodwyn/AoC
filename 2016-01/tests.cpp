#include <memory>
#include <gtest/gtest.h>

#include "year2016day01.h"

using namespace AoC::Year2016Day01;

class MapTest : public ::testing::Test {
public:
    virtual void SetUp() override {
        mapTraveler.reset(new MapTraveler);
    }

    virtual void TearDown() override {
        mapTraveler.reset(nullptr);
    }

    std::unique_ptr<MapTraveler> mapTraveler;
};

TEST_F(MapTest, CanGetDefaultPosition) {
    auto position = mapTraveler->currentPosition();
    EXPECT_EQ(0, position.first);
    EXPECT_EQ(0, position.second);
}

TEST_F(MapTest, CanGetDefaultDirection) {
    EXPECT_EQ(Facing::North(), mapTraveler->currentFacing());
}

TEST_F(MapTest, CanTurnToTheRight) {
    mapTraveler->turn(Turn::Right());
    EXPECT_EQ(Facing::East(), mapTraveler->currentFacing());
}

TEST_F(MapTest, CanTurnToTheLeft) {
    mapTraveler->turn(Turn::Left());
    EXPECT_EQ(Facing::West(), mapTraveler->currentFacing());
}

TEST_F(MapTest, CanTravelNorth) {
    mapTraveler->travel(17);
    auto position = mapTraveler->currentPosition();
    EXPECT_EQ(0, position.first);
    EXPECT_EQ(17, position.second);
}

TEST_F(MapTest, CanTravelEast) {
    mapTraveler->turn(Turn::Right());
    mapTraveler->travel(19);
    auto position = mapTraveler->currentPosition();
    EXPECT_EQ(19, position.first);
    EXPECT_EQ(0, position.second);
}

TEST_F(MapTest, CanTravelWest) {
    mapTraveler->turn(Turn::Left());
    mapTraveler->travel(13);
    auto position = mapTraveler->currentPosition();
    EXPECT_EQ(-13, position.first);
    EXPECT_EQ(0, position.second);
}

TEST_F(MapTest, CanTravelSouth) {
    mapTraveler->turn(Turn::Left());
    mapTraveler->turn(Turn::Left());
    mapTraveler->travel(7);
    auto position = mapTraveler->currentPosition();
    EXPECT_EQ(0, position.first);
    EXPECT_EQ(-7, position.second);
}

TEST_F(MapTest, CanTravelSouthThenWest) {
    mapTraveler->turn(Turn::Left());
    mapTraveler->turn(Turn::Left());
    mapTraveler->travel(7);
    mapTraveler->turn(Turn::Right());
    mapTraveler->travel(11);
    auto position = mapTraveler->currentPosition();
    EXPECT_EQ(-11, position.first);
    EXPECT_EQ(-7, position.second);
}

TEST_F(MapTest, CanGetShortestPathDistanceFromOrigin) {
    mapTraveler->turn(Turn::Left());
    mapTraveler->turn(Turn::Left());
    mapTraveler->travel(7);
    mapTraveler->turn(Turn::Right());
    mapTraveler->travel(11);
    mapTraveler->turn(Turn::Right());
    mapTraveler->travel(3);
    auto distance = mapTraveler->distanceFromOrigin();
    EXPECT_EQ(15, distance);
}
