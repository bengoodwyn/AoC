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

std::vector<std::map<char, int>> columnFrequencies;

void processLine(std::string line) {
	if (line.length() > columnFrequencies.size()) {
		columnFrequencies.resize(line.length());
	}

	int i = 0;
	for (auto character: line) {
		columnFrequencies[i][character] += 1;
		++i;
	}
}

std::string correctedMessage() {
	std::string message;
	for (auto column: columnFrequencies) {
		int lowestFrequency = std::numeric_limits<int>::max();
		int leastFrequentCharacter = '\0';
		for (auto frequency : column) {
			if (frequency.second < lowestFrequency) {
				lowestFrequency = frequency.second;
				leastFrequentCharacter = frequency.first;
			}
		}
		message += leastFrequentCharacter;
	}
	return message;
}

int main(int argc, const char* argv[]) {
	std::ifstream input("input");
	std::string line;
	while (std::getline(input, line)) {
		processLine(line);
	}
	std::cout << correctedMessage() << std::endl;
	return 0;
}
