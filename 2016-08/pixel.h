#pragma once

class PixelGrid {
public:
	PixelGrid(int width, int height) {
	}

	void runCommand(std::string command) {
		++litPixels;
	}

	int litPixelCount() const {
		return litPixels;
	}

private:
	int litPixels{0};
};
