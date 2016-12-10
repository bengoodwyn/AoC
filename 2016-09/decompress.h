#pragma once

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

	std::uint64_t run(std::istream& input, std::ostream& output) {
		input.peek();
		if (input.eof()) {
			return 0;
		}

		std::uint64_t length = 0;
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

			length = charactersToRead * timesToRepeat;
			atParen = false;
		} else {
			std::string raw;
			std::getline(input, raw, '(');
			raw = stripSpace(raw);
			if (raw.length() > 0) {
				std::cout << "RAW '" << stripSpace(raw) << "'" << std::endl;
				output << raw;
			}

			length = raw.length();
			atParen = true;
		}

		return length;
	}

private:
	bool atParen{false};
};
