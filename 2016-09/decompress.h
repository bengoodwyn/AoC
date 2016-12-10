#pragma once

#include <iostream>

class Decompressor {
public:
	static bool run(std::istream& input, std::ostream& output) {
		if ('(' == input.peek()) {
			input.get();
			std::string command;
			std::getline(input, command, ')');
		} else {
			std::string in;
			input >> in;
			output << in;
		}
		return !input.eof();
	}
};
