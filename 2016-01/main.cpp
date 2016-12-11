#include <cassert>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <set>
#include "Traveler.h"

using namespace AoC;

class CommandProcessor {
public:
    virtual void processCommand(std::istream& input) {
        char direction;
        input >> std::skipws >> direction;
        turn(direction);

        int distance;
        input >> distance;
        travel(distance);
    }

    virtual int distanceFromOrigin() {
        return traveler.distanceFromOrigin();
    }

protected:
    virtual void turn(char direction) {
        if ('R' == direction) {
            traveler.turn(Turn::Right);
        } else if ('L' == direction) {
            traveler.turn(Turn::Left);
        } else {
            abort();
        }
    }

    virtual void travel(int distance) {
        traveler.travel(distance);
    }

    Traveler traveler;
};

class CommandProcessor2 : public CommandProcessor, public Traveler::Follower {
public:
    CommandProcessor2() {
        traveler.addFollower(*this);
    }

    virtual void onTravelerMoved(Traveler& traveler) override {
        auto currentPosition = traveler.currentPosition();
        if (visitedPositions.find(currentPosition) != visitedPositions.end()) {
            if (distance < 0) {
                distance = traveler.distanceFromOrigin();
            }
        } else {
            visitedPositions.insert(currentPosition);
        }
    }

    virtual int distanceFromOrigin() override {
        return distance;
    }

protected:
    virtual void travel(int distance) override {
        for (auto i = 0; i < distance; ++i) {
            CommandProcessor::travel(1);
        }
    }

    int distance{-1};
    std::set<Traveler::Position> visitedPositions;
};

int main(int argc, const char* argv[]) {
    bool part2 = (argc > 1 && argv[1][0] == '2');
    std::unique_ptr<CommandProcessor> commandProcessor(part2 ? (new CommandProcessor2) : (new CommandProcessor));
    std::ifstream input("input");
    std::string command;
    while (!input.eof()) {
        commandProcessor->processCommand(input);
        char comma;
        input >> comma;
        assert(comma == ',');
    }
    std::cout << commandProcessor->distanceFromOrigin() << std::endl;
    return 0;
}
