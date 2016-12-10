#pragma once

#include <sstream>

class PixelGrid {
public:
	PixelGrid(int width, int height) {
	}

	void runCommand(std::string line) {
		std::stringstream stream(line);
		std::string command;
		stream >> command;
		if (command == std::string("rect")) {
			rect(stream);
		}
	}

	int litPixelCount() const {
		return litPixels;
	}

private:
	void rect(std::istream& stream) {
		int width;
		int height;
		stream >> width;
		stream.get();
		stream >> height;
		litPixels += width * height;
	}

	int litPixels{0};
};
