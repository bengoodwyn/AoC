#pragma once

#include <iostream>
#include <list>
#include <map>

using Value = std::uint64_t;

class Bot;

class Bot {
public:
	void receive(Value value) {
		if (values.empty() || (value < values.front())) {
			values.push_front(value);
		} else {
			values.push_back(value);
		}
	}

	Value takeHighValue() {
		auto value = values.back();
		values.pop_back();
		return value;
	}

	void giveHighValueTo(Bot& otherBot) {
		auto value = takeHighValue();
		otherBot.receive(value);
	}

	Value takeLowValue() {
		auto value = values.front();
		values.pop_front();
		return value;
	}

	void giveLowValueTo(Bot& otherBot) {
		auto value = takeLowValue();
		otherBot.receive(value);
	}

private:
	std::list<Value> values;
};

class Output {
public:
	void receive(Value value) {
	}
};

class Factory {
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

		} else {
			throw BadCommand();
		}
	}

	void giveValueToBot(std::istream& stream) {
		Value value;
		stream >> value;
		std::string junk;
		stream >> junk >> junk >> junk;
		int id;
		stream >> id;
		bot(id).receive(value);
	}

	Bot& bot(int id) {
		return bots[id];
	}

private:
	std::map<int, Bot> bots;
};
