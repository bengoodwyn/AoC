#include <memory>
#include <gtest/gtest.h>

#include <string>

class KeyGenerator {
public:
    KeyGenerator(std::string salt) : salt(salt) {
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

TEST_F(KeyGeneratorTests, Template) {
    ASSERT_TRUE(true);
}
