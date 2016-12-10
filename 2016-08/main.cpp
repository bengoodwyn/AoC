#include <fstream>
#include "pixel.h"

int main(int argc, const char* argv[]) {
	std::ifstream input("input");
	std::string line;
	PixelGrid grid;
	while (std::getline(input, line)) {
		grid.runCommand(line);
	}
}
