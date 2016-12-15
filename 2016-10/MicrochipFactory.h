#pragma once

#include <array>
#include <iostream>
#include <map>
#include <sstream>

#include "Bot.h"
#include "OutputBin.h"

class MicrochipFactory {
public:
    MicrochipFactory(Bot::Comparator comparator = Bot::DefaultComparator) : comparator{comparator} {
    }

    class BadCommand {
    };

    void execute(std::string command) {
        std::stringstream stream(command);
        std::string commandClass;
        std::getline(stream, commandClass, ' ');
        if (commandClass == "value") {
            giveValueToBot(stream);
        } else if (commandClass == "bot") {
            connectBot(stream);
        } else {
            throw BadCommand();
        }
    }

    void connectBot(std::istream& stream) {
        int sourceId;
        std::string destinationType;
        int targetId;
        std::array<ValueReceiver*, 2> targets;

        stream >> sourceId;
        for (int i = 0; i < 2; i++) {
            stream >> destinationType >> targetId;
            if (destinationType == "bot") {
                targets[i] = &bot(targetId);
            } else if (destinationType == "output") {
                targets[i] = &output(targetId);
            } else {
                throw BadCommand();
            }
        }

        bot(sourceId).connectTo(targets[0], targets[1]);
    }

    void giveValueToBot(std::istream& stream) {
        Value value;
        std::string destinationType;
        int id;

        stream >> value >> destinationType >> id;
        if (destinationType != "bot") {
            throw BadCommand();
        }

        bot(id).receive(value);
    }

    Value reproduceOutput(int id) {
        return output(id).reproduce();
    }

private:
    Bot& bot(int id) {
        auto iter = bots.find(id);
        if (bots.end() == iter) {
            return bots.emplace(id, Bot{id, comparator}).first->second;
        } else {
            return iter->second;
        }
    }

    OutputBin& output(int id) {
        auto iter = outputs.find(id);
        if (outputs.end() == iter) {
            return outputs.emplace(id, OutputBin{id}).first->second;
        } else {
            return iter->second;
        }
    }

    Bot::Comparator comparator;
    std::map<int, Bot> bots;
    std::map<int, OutputBin> outputs;
};
