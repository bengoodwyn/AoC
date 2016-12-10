#include <cassert>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <array>
#include <map>
#include <list>
#include <set>
#include <sstream>
#include <vector>
#include <limits>

bool processLine(std::string line) {
	int hypernet_count = 0;
	int abba_count = 0;
	for (int start = 0; start <= (line.length() - 4); ++start) {
		if ((std::string::npos == line.substr(start, 4).find('[')) &&
			(std::string::npos == line.substr(start, 4).find(']'))) {
			if (line.at(start) == line.at(start + 3) && line.at(start + 1) == line.at(start + 2)) {
				if (line.at(start) != line.at(start + 1)) {
					if (0 == hypernet_count) {
						++abba_count;
					} else {
						return false;
					}
				}
			}
		}
		if (line.at(start) == '[') {
			++hypernet_count;
		} else if (line.at(start) == ']') {
			--hypernet_count;
			assert(hypernet_count >= 0);
		}
	}
	return abba_count > 0;
}

int main(int argc, const char* argv[]) {
	std::ifstream input("input");
	std::string line;
	int count = 0;
	while (std::getline(input, line)) {
		if (processLine(line)) {
			std::cout << line << std::endl << std::endl;
			++count;
		}
	}
	std::cout << count << std::endl;
	return 0;
}
