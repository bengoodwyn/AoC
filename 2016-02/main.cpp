#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <array>

class Key {
public:
	const int digit;
	const int up;
	const int left;
	const int right;
	const int down;

	Key(int digit
		, int up
		, int left
		, int right
		, int down)
		: digit(digit), up(up), left(left), right(right), down(down) {
	}

	int move(char direction) const {
		switch (direction) {
			case 'U':
				return up;
				break;
			case 'L':
				return left;
				break;
			case 'R':
				return right;
				break;
			case 'D':
				return down;
				break;
		}
		throw std::exception();
	}
};

const std::array<Key
	, 10> keys = {Key(0
	, 0
	, 0
	, 0
	, 0), Key(1
	, 1
	, 1
	, 2
	, 4), Key(2
	, 2
	, 1
	, 3
	, 5), Key(3
	, 3
	, 2
	, 3
	, 6), Key(4
	, 1
	, 4
	, 5
	, 7), Key(5
	, 2
	, 4
	, 6
	, 8), Key(6
	, 3
	, 5
	, 6
	, 9), Key(7
	, 4
	, 7
	, 8
	, 7), Key(8
	, 5
	, 7
	, 9
	, 8), Key(9
	, 6
	, 8
	, 9
	, 9)};

int currentKey = 5;

int main() {
	std::ifstream input("input");
	std::string line;
	while (std::getline(input
		, line)) {
		for (auto move : line) {
			currentKey = keys[currentKey].move(move);
		}
		std::cout << currentKey << std::endl;
	}
	return 0;
}
