#pragma once

#include <iostream>
#include <list>
#include <map>
#include <sstream>

using Value = std::uint64_t;

class Bot;

class Bot {
public:
	const int id;

	Bot(int id)
		: id{id} {
	}

	void receive(Value value) {
		if (values.empty() || (value < values.front())) {
			values.push_front(value);
		} else {
			values.push_back(value);
		}
	}

	Value takeHighValue() {
		logComparison();
		auto value = values.back();
		values.pop_back();
		return value;
	}

	void giveHighValueTo(Bot& otherBot) {
		auto value = takeHighValue();
		otherBot.receive(value);
	}

	Value takeLowValue() {
		logComparison();
		auto value = values.front();
		values.pop_front();
		return value;
	}

	void giveLowValueTo(Bot& otherBot) {
		auto value = takeLowValue();
		otherBot.receive(value);
	}

private:
	void logComparison() {
		if (values.size() > 1) {
			std::cout << "bot " << id << " is comparing " << values.front() << " to " << values.back() << std::endl;
		}
	}
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
		Value value;
		std::string destinationType;

		stream >> sourceId;
		Bot& sourceBot = bot(sourceId);

		for (int i = 0; i < 2; i++) {
			stream >> junk; // gives OR and
			stream >> which;
			stream >> junk;
			stream >> destinationType;
			stream >> targetId;
			if ("bot" == destinationType) {
				Bot& targetBot = bot(targetId);

				if ("low" == which) {
					sourceBot.giveLowValueTo(targetBot);
				} else {
					sourceBot.giveHighValueTo(targetBot);
				}
			} else {
				if ("low" == which) {
					sourceBot.takeLowValue();
				} else {
					sourceBot.takeHighValue();
				}

			}
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
		auto iter = bots.find(id);
		if (bots.end() == iter) {
			return (*bots.emplace(std::make_pair(id, Bot{id})).first).second;
		} else {
			return iter->second;
		}
	}

private:
	std::map<int, Bot> bots;
};
