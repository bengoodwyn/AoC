#include <memory>
#include <gtest/gtest.h>

#include <string>

class KeyGenerator {
public:
    KeyGenerator(std::string salt) : salt(salt) {
    }

    std::string saltInteger(int integer) {
        return salt + std::to_string(integer);
    }

private:
    std::string salt;
};

class KeyGeneratorTests : public ::testing::Test {
public:
    virtual void SetUp() override {
        keyGenerator.reset(new KeyGenerator("abc"));
    }

    virtual void TearDown() override {
        keyGenerator.reset();
    }

    std::unique_ptr<KeyGenerator> keyGenerator;
};

TEST_F(KeyGeneratorTests, CanCombineSaltWithIntegerIndex) {
    ASSERT_EQ("abc123", keyGenerator->saltInteger(123));
}
