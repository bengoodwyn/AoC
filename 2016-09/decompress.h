#pragma once

#include <iostream>

class Decompressor {
public:
	static bool run(std::istream& input, std::ostream& output) {
		std::string in;
		input >> in;
		output << in;
		return !input.eof();
	}
};
