#include <memory>
#include <gtest/gtest.h>

#include <array>
#include <cstdio>
#include <string>
#include <openssl/md5.h>

class KeyGenerator {
public:
    KeyGenerator(std::string salt) : salt(salt) {
    }

    std::string saltInteger(int integer) {
        return salt + std::to_string(integer);
    }

    const char* digest(std::string input) {
        static unsigned char digest[16];
        static std::array<char, (sizeof(digest) * 2) + 1> strDigest;
        MD5(reinterpret_cast<const unsigned char*>(input.data()), input.length(), digest);
        snprintf(&strDigest.at(0), strDigest.size(), "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
            digest[0], digest[1], digest[2], digest[3], digest[4], digest[5], digest[6], digest[7], digest[8],
            digest[9], digest[10], digest[11], digest[12], digest[13], digest[14], digest[15]);
        return &strDigest.at(0);
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

TEST_F(KeyGeneratorTests, CanGetDigestOfAString) {
    ASSERT_EQ("0034e0923cc38887a57bd7b1d4f953df", std::string(keyGenerator->digest("abc18")));
}
