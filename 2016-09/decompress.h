#pragma once

#include <iostream>

class Decompressor {
public:
	bool run(std::istream& input, std::ostream& output) {
		std::string in;
		input >> in;
		output << in;
		return false;
	}
};