#include <cassert>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <set>
#include "year2016day01.h"

using namespace AoC::Year2016Day01;

class CommandProcessor {
public:
    virtual bool processCommand(std::istream& input) {
        char direction;
        input >> std::skipws >> direction;
        turn(direction);

        int distance;
        input >> distance;
        return travel(distance);
    }

    int distanceFromOrigin() {
        return traveler.distanceFromOrigin();
    }

protected:
    virtual void turn(char direction) {
        if ('R' == direction) {
            std::cerr << "Turning Right" << std::endl;
            traveler.turn(Turn::Right());
        } else if ('L' == direction) {
            std::cerr << "Turning Left" << std::endl;
            traveler.turn(Turn::Left());
        } else {
            abort();
        }
    }

    virtual bool travel(int distance) {
        std::cerr << "Traveling " << distance << std::endl;
        traveler.travel(distance);
        return true;
    }

    MapTraveler traveler;
};

class CommandProcessor2 : public CommandProcessor {
protected:
    virtual bool travel(int distance) override {
        for (int i = 0; i < distance; ++i) {
            CommandProcessor::travel(1);
            if (visitedPositions.end() != visitedPositions.find(traveler.currentPosition())) {
                return false;
            } else {
                visitedPositions.insert(traveler.currentPosition());
            }
        }
        return true;
    }

    std::set<MapTraveler::Position> visitedPositions;
};

int main(int argc, const char* argv[]) {
    bool part2 = (argc > 1 && argv[1][0] == '2');
    std::unique_ptr<CommandProcessor> commandProcessor(part2 ? (new CommandProcessor2) : (new CommandProcessor));
    std::ifstream input("input");
    std::string command;
    while (!input.eof()) {
        if (!commandProcessor->processCommand(input)) {
            break;
        }
        char comma;
        input >> comma;
        assert(comma == ',');
    }
    std::cout << commandProcessor->distanceFromOrigin() << std::endl;
    return 0;
}
