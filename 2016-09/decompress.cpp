#include <gtest/gtest.h>
#include <sstream>

#include "decompress.h"

class DecompressTest : public ::testing::Test {
protected:
    virtual void SetUp() override {
        decompressor.reset(new Decompressor);
    }

    virtual void TearDown() override {
        decompressor.reset(nullptr);
    }

    void run(std::string input_string, std::string expected_output, bool recursive) {
        std::stringstream input(input_string);
        std::uint64_t totalLength{0};
        std::uint64_t readLength;
        while (0 != (readLength = decompressor->run(input, recursive))) {
            totalLength += readLength;
        }
        EXPECT_EQ(expected_output.length(), totalLength);
    }

    std::unique_ptr<Decompressor> decompressor;
};

TEST_F(DecompressTest, ProducesAnEmptyStreamFromAnEmptyStream) {
    run("", "", false);
}

TEST_F(DecompressTest, CopiesAnInputStreamToAnOutputStream) {
    run("simple", "simple", false);
}

TEST_F(DecompressTest, CanRepeatAStringOnce) {
    run("(3x1)abc", "abc", false);
}

TEST_F(DecompressTest, CanRepeatAStringTwice) {
    run("(3x2)abc", "abcabc", false);
}

TEST_F(DecompressTest, CanRunTwoCommandsWithJunkInTheMiddle) {
    run("(3x2)abc123(3x3)xyz", "abcabc123xyzxyzxyz", false);
}

TEST_F(DecompressTest, CanSkipANestedCommand) {
    run("(11x2)ab(2x2)xy12", "ab(2x2)xy12ab(2x2)xy12", false);
}

TEST_F(DecompressTest, CanRunANestedCommand) {
    run("(11x2)ab(2x2)xy12", "abxyxy12abxyxy12", true);
}
