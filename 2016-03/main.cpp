#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <array>
#include <sstream>

int main() {
	std::ifstream input("input");
	std::string line;
	int valid = 0;
	int y = 0;
	while (std::getline(input, line)) {
		std::stringstream stream(line);
		std::array<std::array<int, 3>, 3> sides;
		stream >> sides[0][y] >> sides[1][y] >> sides[2][y];
		if (2 == y) {
			for (auto column = 0; column < 3; ++column) {
				std::sort(sides[column].begin(), sides[column].end());
				if (sides[column][0] + sides[column][1] > sides[column][2]) {
					++valid;
				}
			}
			y = 0;
		} else {
			++y;
		}
	}
	std::cout << valid << std::endl;
	return 0;
}
