#pragma once

#include <sstream>

class PixelGrid {
private:
	using Pixel = char;
	using Grid = std::vector<Pixel>;

public:
	class UnknownCommand {
	};

	PixelGrid(int width, int height)
		: pixels(width * height), width(width) {
	}

	void runCommand(std::string line) {
		std::stringstream stream(line);
		std::string command;
		stream >> command;
		if (command == std::string("rect")) {
			rect(stream);
		} else {
			throw UnknownCommand();
		}
	}

	int litPixelCount() const {
		int count = 0;
		for (auto pixel : pixels) {
			count += pixel;
		}
		return count;
	}

private:
	void rect(std::istream& stream) {
		std::pair<int, int> rect;
		stream >> rect.first;
		stream.get();
		stream >> rect.second;
		for (int row = 0; row < rect.second; ++row) {
			for (int col = 0; col < rect.first; ++col) {
				at(row, col) = 1;
			}
		}
	}

	Pixel& at(int row, int col) {
		return pixels.at(row * width + col);
	}

	Grid pixels;
	int width;
};
