#pragma once

#include <ctype.h>
#include <iostream>

class Decompressor {
public:
	static bool run(std::istream& input, std::ostream& output) {
		int charactersToRead = 1;
		int timesToRepeat = 1;

		if ('(' == input.peek()) {
			input.get();
			std::string command;
			std::getline(input, command, ')');
			std::stringstream command_stream(command);
			command_stream >> charactersToRead;
			command_stream.get();
			command_stream >> timesToRepeat;
		}

		std::string characters;
		for (int i = 0; !input.eof() && i < charactersToRead; ++i) {
			char character = input.get();
			while (isspace(character) && !input.eof()) {
				character = input.get();
			}
			characters += character;
		}

		for (int i = 0; i < timesToRepeat; ++i) {
			output << characters;
		}

		return !input.eof();
	}
};
