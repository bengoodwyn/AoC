#include <gtest/gtest.h>
#include <sstream>

#include "decompress.h"

class DecompressTest
	: public ::testing::Test {
protected:
	virtual void SetUp() override {
		input.clear();
		output.clear();
		decompressor.reset(new Decompressor);
	}

	virtual void TearDown() override {
		decompressor.reset(nullptr);
	}

	std::stringstream input;
	std::stringstream output;
	std::unique_ptr<Decompressor> decompressor;
};

TEST_F(DecompressTest, ProducesAnEmptyStreamFromAnEmptyStream) {
	while (decompressor->run(input, output)) {
	}
	EXPECT_EQ(0, output.str().length());
}

TEST_F(DecompressTest, CopiesAnInputStreamToAnOutputStream) {
	std::string input_string("simple");
	input << input_string;
	while (decompressor->run(input, output)) {
	}
	EXPECT_EQ(input_string, output.str());
}
