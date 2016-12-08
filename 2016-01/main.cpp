#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

std::string nextCommand(std::istream& input) {
	std::string command;
	if (std::getline(input
		, command
		, ',')) {
		while (!command.empty() && std::isspace(command.at(0))) {
			command.erase(0
				, 1);
		}
		while (!command.empty() && std::isspace(command.at(command.length() - 1))) {
			command.erase(command.length() - 1);
		}
	}
	return command;
}

enum Direction {
	NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3
};

int currentDirection = NORTH;
int x = 0;
int y = 0;

void turn(char direction) {
	int delta;
	switch (direction) {
		case 'R':
			delta = 1;
			break;
		case 'L':
			delta = -1;
			break;
		default:
			throw std::exception();
	}
	currentDirection += delta;
	if (currentDirection < 0)
		currentDirection += 4;
	if (currentDirection > 3)
		currentDirection -= 4;
	std::cout << direction << ": new direction: " << currentDirection << std::endl;
}

void go(int distance) {
	switch (currentDirection) {
		case NORTH:
			y += distance;
			break;
		case EAST:
			x += distance;
			break;
		case SOUTH:
			y -= distance;
			break;
		case WEST:
			x -= distance;
			break;
		default:
			throw std::exception();
	}
	std::cout << distance << ": x=" << x << " y=" << y << std::endl;
}

void processCommand(std::string command) {
	turn(command.at(0));
	go(std::stoi(command.substr(1)));
}

int main() {
	std::ifstream input("input");
	std::string command;
	while (!(command = nextCommand(input)).empty()) {
		processCommand(command);
	}
	std::cout << "Distance: " << std::abs(x) + std::abs(y) << std::endl;
	return 0;
}
