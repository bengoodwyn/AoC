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
