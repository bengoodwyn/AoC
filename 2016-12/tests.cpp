#include <memory>
#include <sstream>
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

TEST_F(VmTest, CanLoadInstructionsFromAStream) {
    std::stringstream stream;
    ASSERT_NO_THROW(vm->load(stream));
}

TEST_F(VmTest, CanIncrementAToMakeIt1) {
    std::stringstream stream("inc a");
    vm->load(stream);
    vm->execute();
    ASSERT_EQ(1, vm->read('a'));
}
