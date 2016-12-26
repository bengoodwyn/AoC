#include <memory>
#include <gtest/gtest.h>
#include "Vm.h"

using namespace AoC;

class VmTest : public ::testing::Test {
public:
    virtual void SetUp() override {
        vm.reset(new Vm);
    }

    virtual void TearDown() override {
        vm.reset();
    }

    std::unique_ptr<Vm> vm;
};

TEST_F(VmTest, CanGetValueOfRegisterA) {
    ASSERT_EQ(vm->read('a'), 0);
}
