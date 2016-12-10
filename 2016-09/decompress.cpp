#include <gtest/gtest.h>
#include <sstream>

#include "decompress.h"

class DecompressTest
	: public ::testing::Test {
protected:
	virtual void SetUp() override {
		decompressor.reset(new Decompressor);
	}

	virtual void TearDown() override {
		decompressor.reset(nullptr);
	}

	void run(std::string input_string, std::string expected_output) {
		std::stringstream input(input_string);
		std::stringstream output;
		while (decompressor->run(input, output)) {
		}
		EXPECT_EQ(expected_output, output.str());
	}

	std::unique_ptr<Decompressor> decompressor;
};

TEST_F(DecompressTest, ProducesAnEmptyStreamFromAnEmptyStream) {
	run("", "");
}

TEST_F(DecompressTest, CopiesAnInputStreamToAnOutputStream) {
	run("simple", "simple");
}

TEST_F(DecompressTest, IgnoresWhiteSpace) {
	run("simple simple\nsimple", "simplesimplesimple");
}

TEST_F(DecompressTest, CanRepeatAStringOnce) {
	run("(3x1)abc", "abc");
}

TEST_F(DecompressTest, CanRepeatAStringTwice) {
	run("(3x2)abc", "abcabc");
}

TEST_F(DecompressTest, CanRunTwoCommandsWithJunkInTheMiddle) {
	run("(3x2)abc123(3x3)xyz", "abcabc123xyzxyzxyz");
}
