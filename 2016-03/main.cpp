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
	while (std::getline(input, line)) {
		std::stringstream stream(line);
		std::array<int, 3> sides;
		stream >> sides[0] >> sides[1] >> sides[2];
		std::sort(sides.begin(), sides.end());
		if (sides[0] + sides[1] > sides[2]) {
			++valid;
		}
	}
	std::cout << valid << std::endl;
	return 0;
}
