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
			int width;
			int height;
			stream >> width;
			stream.get();
			stream >> height;
			litPixels += width * height;
		}
	}

	int litPixelCount() const {
		return litPixels;
	}

private:
	int litPixels{0};
};
