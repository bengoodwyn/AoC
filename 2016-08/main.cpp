#include <fstream>
#include <iostream>
#include "pixel.h"

int main(int argc, const char* argv[]) {
	std::ifstream input("input");
	std::string line;
	PixelGrid grid;
	while (std::getline(input, line)) {
		grid.runCommand(line);
	}
	std::cout << grid.litPixelCount() << std::endl;
	return 0;
}
