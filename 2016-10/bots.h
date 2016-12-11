#pragma once

#include <iostream>
#include <list>
#include <map>
#include <sstream>

using Value = std::uint64_t;

class Bot;

class ValueReceiver {
public:
    virtual std::string receiverId() const = 0;
    virtual void receive(Value value) = 0;
};

class Bot : public ValueReceiver {
public:
    class Listener {
    public:
        virtual void OnBotFull(Bot& bot) = 0;
    };

    const int id;

    Bot(int id, Listener& listener) : id{id}, listener{listener} {
    }

    virtual std::string receiverId() const override {
        std::string receiverId;
        receiverId = "Bot:" + std::to_string(id);
        return receiverId;
    }

    virtual void receive(Value value) override {
        if (values.empty() || (value < values.front())) {
            values.push_front(value);
        } else {
            values.push_back(value);
        }
        if (2 == values.size()) {
            listener.OnBotFull(*this);
        }
    }

    Value takeHighValue() {
        logComparison();
        auto value = values.back();
        values.pop_back();
        return value;
    }

    void giveHighValueTo(ValueReceiver& other) {
        auto value = takeHighValue();
        other.receive(value);
    }

    Value takeLowValue() {
        logComparison();
        auto value = values.front();
        values.pop_front();
        return value;
    }

    void giveLowValueTo(ValueReceiver& other) {
        auto value = takeLowValue();
        other.receive(value);
    }

    int valueCount() const {
        return values.size();
    }

private:
    void logComparison() {
        if (values.size() > 1) {
            if (values.front() == 17 && values.back() == 61) {
                std::cout << "****************";
            }
            std::cout << "bot " << id << " is comparing " << values.front() << " to " << values.back() << std::endl;
        }
    }

    std::list<Value> values;
    Listener& listener;
};

class Output : public ValueReceiver {
public:
    const int id;

    Output(int id = 0) : id{id} {
    }

    virtual std::string receiverId() const override {
        std::string receiverId;
        receiverId = "Output:" + std::to_string(id);
        return receiverId;
    }

    virtual void receive(Value value) override {
        received = value;
    }

    Value reproduce() {
        return received;
    }

private:
    Value received;
};

class Factory : Bot::Listener {
public:
    class BadCommand {
    };

    void execute(std::string command) {
        std::stringstream stream(command);
        std::string commandClass;
        std::getline(stream, commandClass, ' ');
        if (commandClass == "value") {
            giveValueToBot(stream);
        } else if (commandClass == "bot") {
            botGivesValues(stream);
        } else {
            throw BadCommand();
        }
    }

    void botGivesValues(std::istream& stream) {
        std::string junk;
        int sourceId;
        std::string which;
        int targetId;
        std::string destinationType;

        stream >> sourceId;

        ValueReceiver* lowTarget = nullptr;
        ValueReceiver* highTarget = nullptr;
        for (int i = 0; i < 2; i++) {
            stream >> junk; // "gives" OR "and"
            stream >> which;
            stream >> junk;
            stream >> destinationType;
            stream >> targetId;
            if ("bot" == destinationType) {
                if ("low" == which) {
                    lowTarget = &bot(targetId);
                } else {
                    highTarget = &bot(targetId);
                }
            } else {
                if ("low" == which) {
                    lowTarget = &output(targetId);
                } else {
                    highTarget = &output(targetId);
                }
            }
        }

        connections[sourceId] = std::make_pair(lowTarget, highTarget);
        Bot& sourceBot = bot(sourceId);
        if (sourceBot.valueCount() == 2) {
            OnBotFull(sourceBot);
        }
    }

    void giveValueToBot(std::istream& stream) {
        Value value;
        stream >> value;
        std::string junk;
        stream >> junk >> junk >> junk;
        int id;
        stream >> id;

        Bot& targetBot = bot(id);
        targetBot.receive(value);
    }

    virtual void OnBotFull(Bot& fullBot) override {
        auto connection = connections.find(fullBot.id);
        if (connections.end() != connection) {
            fullBot.giveLowValueTo(*connection->second.first);
            fullBot.giveHighValueTo(*connection->second.second);
        }
    }

    Bot& bot(int id) {
        auto iter = bots.find(id);
        if (bots.end() == iter) {
            return (*bots.emplace(std::make_pair(id, Bot{id, *this})).first).second;
        } else {
            return iter->second;
        }
    }

    Value reproduceOutput(int id) {
        Output& bin = output(id);
        return bin.reproduce();
    }

private:
    Output& output(int id) {
        auto iter = outputs.find(id);
        if (outputs.end() == iter) {
            return (*outputs.emplace(std::make_pair(id, Output{id})).first).second;
        } else {
            return iter->second;
        }
    }

    std::map<int, Bot> bots;
    std::map<int, Output> outputs;
    std::map<int, std::pair<ValueReceiver*, ValueReceiver*>> connections;
};
