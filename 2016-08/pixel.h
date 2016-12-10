#pragma once

#include <sstream>
#include <vector>

class PixelGrid {
private:
	using Pixel = char;
	using Grid = std::vector<Pixel>;

public:
	class UnknownCommand {
	};

	class MalformedCommand {
	};

	PixelGrid(int width, int height)
		: pixels(width * height), width{width}, height{height} {
	}

	void runCommand(std::string line) {
		std::stringstream stream(line);
		stream >> std::skipws;
		std::string command;
		stream >> command;
		if (command == std::string("rect")) {
			rect(stream);
		} else if (command == "rotate") {
			rotate(stream);
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

	void print() const {
		for (int row = 0; row < height; ++row) {
			for (int col = 0; col < width; ++col) {
				std::cout << (at(row, col) ? '#' : '.');
			}
			std::cout << std::endl;
		}
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

	void rotate(std::istream& stream) {
		std::string direction;
		stream >> direction;
		if (direction == "row") {
			rotateRow(stream);
		} else if (direction == "column") {
			rotateColumn(stream);
		} else {
			throw MalformedCommand();
		}
	}

	void rotateRow(std::istream& stream) {
		char y;
		stream >> y;
		if (y != 'y') {
			throw MalformedCommand();
		}

		char equals;
		stream >> equals;
		if (equals != '=') {
			throw MalformedCommand();
		}

		int row;
		stream >> row;

		std::string by;
		stream >> by;

		int distance;
		stream >> distance;

		rotateRow(row, distance);
	}

	void rotateColumn(std::istream& stream) {
		char x;
		stream >> x;
		if (x != 'x') {
			throw MalformedCommand();
		}

		char equals;
		stream >> equals;
		if (equals != '=') {
			throw MalformedCommand();
		}

		int col;
		stream >> col;

		std::string by;
		stream >> by;

		int distance;
		stream >> distance;

		rotateColumn(col, distance);
	}

	void rotateRow(int row, int distance) {
		// :TODO: This is a dumb, but easy implementation...
		for (int i = 0; i < distance; ++i) {
			for (int col = 0; col < (width - 1); ++col) {
				std::swap(at(row, col), at(row, width - 1));
			}
		}
	}

	void rotateColumn(int col, int distance) {
		// :TODO: This is a dumb, but easy implementation...
		for (int i = 0; i < distance; ++i) {
			for (int row = 0; row < (height - 1); ++row) {
				std::swap(at(row, col), at(height - 1, col));
			}
		}
	}

	Pixel at(int row, int col) const {
		return pixels.at(index(row, col));
	}

	Pixel& at(int row, int col) {
		return pixels.at(index(row, col));
	}

	int index(int row, int col) const {
		return row * width + col;
	}

	Grid pixels;
	const int width;
	const int height;
};
