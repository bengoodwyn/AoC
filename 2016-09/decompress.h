#pragma once

#include <ctype.h>
#include <iostream>

class Decompressor {
public:
	static std::string stripSpace(std::string source) {
		std::stringstream input(source);
		std::stringstream output;
		std::string str;
		while (input >> std::skipws >> str) {
			output << str;
		}
		return output.str();
	}

	bool run(std::istream& input, std::ostream& output) {
		input.peek();
		if (input.eof()) {
			return false;
		}

		if (atParen || ('(' == input.peek())) {
			if (!atParen) {
				input.get();
			}
			std::string command;
			std::getline(input, command, ')');

			int charactersToRead;
			int timesToRepeat;
			std::stringstream command_stream(command);
			command_stream >> charactersToRead;
			command_stream.get();
			command_stream >> timesToRepeat;

			std::string characters(charactersToRead, '\0');
			input.read(&characters.at(0), charactersToRead);
			characters = stripSpace(characters);

			std::cout << "COMMAND: " << command << " " << charactersToRead << " " << timesToRepeat << " '" << characters
				<< "'" << std::endl;
			for (int i = 0; i < timesToRepeat; ++i) {
				output << characters;
			}

			atParen = false;
		} else {
			std::string raw;
			std::getline(input, raw, '(');
			raw = stripSpace(raw);
			if (raw.length() > 0) {
				std::cout << "RAW '" << stripSpace(raw) << "'" << std::endl;
				output << raw;
			}

			atParen = true;
		}

		return !input.eof();
	}

private:
	bool atParen{false};
};
