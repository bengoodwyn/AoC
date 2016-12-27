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

    void run(std::string instructions) {
        std::stringstream stream(instructions);
        vm->load(stream);
        vm->execute();
    }

    std::unique_ptr<Vm> vm;
};

TEST_F(VmTest, CanGetValueOfRegisterA) {
    ASSERT_EQ(vm->read('a'), 0);
}

TEST_F(VmTest, CanIncrementAToMakeIt1) {
    run("inc a");
    ASSERT_EQ(1, vm->read('a'));
}

TEST_F(VmTest, CanIncrementATwiceToMakeIt2) {
    run("inc a\ninc a");
    ASSERT_EQ(2, vm->read('a'));
}

TEST_F(VmTest, CanDecrementATwiceToMakeItNegative2) {
    run("dec a\ndec a");
    ASSERT_EQ(-2, vm->read('a'));
}

TEST_F(VmTest, CanIncrementBTwiceThenCopyToA) {
    run("inc b\ninc b\ncpy b a");
    ASSERT_EQ(2, vm->read('a'));
}

TEST_F(VmTest, CanCopyImmediateValueToA) {
    run("cpy 99 a");
    ASSERT_EQ(99, vm->read('a'));
}

TEST_F(VmTest, CanSkipJnzWhenZero) {
    run("jnz a 999\ninc a");
    ASSERT_EQ(1, vm->read('a'));
}

TEST_F(VmTest, CanJumpWhenNotZero) {
    run("inc a\njnz a 2\ninc a\ninc a");
    ASSERT_EQ(2, vm->read('a'));
}
