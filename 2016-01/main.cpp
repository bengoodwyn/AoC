#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <set>
#include <tuple>

bool part2;

std::string nextCommand(std::istream& input) {
    std::string command;
    if (std::getline(input, command, ',')) {
        while (!command.empty() && std::isspace(command.at(0))) {
            command.erase(0, 1);
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
std::set<std::pair<int, int>> spots;

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
    if (currentDirection < 0) {
        currentDirection += 4;
    }
    if (currentDirection > 3) {
        currentDirection -= 4;
    }
    std::cerr << direction << ": new direction: " << currentDirection << std::endl;
}

bool go(int distance) {
    for (auto i = 0; i < distance; i++) {
        switch (currentDirection) {
            case NORTH:
                y += 1;
                break;
            case EAST:
                x += 1;
                break;
            case SOUTH:
                y -= 1;
                break;
            case WEST:
                x -= 1;
                break;
            default:
                throw std::exception();
        }
        std::cerr << i << "/" << distance << ": x=" << x << " y=" << y << std::endl;
        auto location = std::pair<int, int>(x, y);
        if (part2 && (spots.end() != spots.find(location))) {
            return true;
        }
        spots.insert(location);
    }
    return false;
}

bool processCommand(std::string command) {
    turn(command.at(0));
    return go(std::stoi(command.substr(1)));
}

int main(int argc, const char* argv[]) {
    part2 = (argc > 1 && argv[1][0] == '2');
    std::ifstream input("input");
    std::string command;
    while (!(command = nextCommand(input)).empty()) {
        if (processCommand(command)) {
            std::cerr << "Repeat visit" << std::endl;
            break;
        }
    }
    std::cout << std::abs(x) + std::abs(y) << std::endl;
    return 0;
}
