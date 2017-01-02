#pragma once

#include <cctype>
#include <iostream>

class Decompressor {
public:
    std::uint64_t run(std::istream& input, bool recursive = false) {
        while (std::isspace(input.peek())) {
            input.get();
        }
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

            if (!recursive || std::string::npos == characters.find('(')) {
                //std::cout << "COMMAND: " << command << " " << charactersToRead << " " << timesToRepeat << " '"
                //	<< characters << "'" << std::endl;
                length = charactersToRead * timesToRepeat;
            } else {
                std::stringstream child_input(characters);
                Decompressor decompressor;
                std::uint64_t childLength = 0;
                std::uint64_t thisLength;
                while (0 != (thisLength = decompressor.run(child_input, recursive))) {
                    childLength += thisLength;
                }
                length += childLength * timesToRepeat;
            }

            atParen = false;
        } else {
            std::string raw;
            std::getline(input, raw, '(');
            length = raw.length();
            atParen = true;
        }

        return length;
    }

private:
    bool atParen{false};
};
