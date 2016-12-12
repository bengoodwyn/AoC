#include <gtest/gtest.h>
#include "Facility.h"

using namespace AoC;

class FacilityTest : public ::testing::Test {
public:
    virtual void SetUp() override {
        facility.reset(new Facility);
    }

    virtual void TearDown() override {
        facility.reset(nullptr);
    }

    std::unique_ptr<Facility> facility;
};

TEST_F(FacilityTest, CanAddFourFloorsAndGetFloorCount) {
    EXPECT_EQ(0, facility->floors());
    facility->addFloor("1");
    EXPECT_EQ(1, facility->floors());
    facility->addFloor("2");
    EXPECT_EQ(2, facility->floors());
    facility->addFloor("3");
    EXPECT_EQ(3, facility->floors());
    facility->addFloor("4");
    EXPECT_EQ(4, facility->floors());
}

TEST_F(FacilityTest, HasAnElevator) {
    EXPECT_NO_THROW(facility->elevator());
}

class ElevatorTest : public ::testing::Test {
public:
    virtual void SetUp() override {
        elevator.reset(new Elevator);
    }

    virtual void TearDown() override {
        elevator.reset(nullptr);
    }

    std::unique_ptr<Elevator> elevator;
};

TEST_F(ElevatorTest, StartsOnTheFirstFloor) {
    EXPECT_EQ(1, elevator->currentFloor());
}

TEST_F(ElevatorTest, WillNotGoUpWhenEmpty) {
    EXPECT_THROW(elevator->up(), Elevator::Empty);
}

TEST_F(ElevatorTest, WillNotGoDownWhenEmpty) {
    EXPECT_THROW(elevator->down(), Elevator::Empty);
}

TEST_F(ElevatorTest, WillNotGoUpWhenOverCapacity) {
    elevator->items.addItem(std::unique_ptr<Item>(new GeneratorItem(std::string("foo"))));
    elevator->items.addItem(std::unique_ptr<Item>(new MicrochipItem(std::string("bar"))));
    elevator->items.addItem(std::unique_ptr<Item>(new MicrochipItem(std::string("baz"))));
    EXPECT_THROW(elevator->up(), Elevator::OverCapacity);
}

TEST_F(ElevatorTest, WillNotGoDownWhenOverCapacity) {
    elevator->items.addItem(std::unique_ptr<Item>(new GeneratorItem(std::string("foo"))));
    elevator->items.addItem(std::unique_ptr<Item>(new MicrochipItem(std::string("bar"))));
    elevator->items.addItem(std::unique_ptr<Item>(new MicrochipItem(std::string("baz"))));
    EXPECT_THROW(elevator->down(), Elevator::OverCapacity);
}
