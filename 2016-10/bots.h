#pragma once

#include <iostream>
#include <list>
#include <map>
#include <sstream>

using Value = std::uint64_t;

class Bot;

class Bot {
public:
	class Listener {
	public:
		virtual void OnBotFull(Bot& bot) = 0;
	};

	const int id;

	Bot(int id, Listener& listener)
		: id{id}, listener{listener} {
	}

	void receive(Value value) {
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

class Output {
public:
	void receive(Value value) {
	}
};

class Factory
	: Bot::Listener {
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
		int lowTarget;
		int highTarget;

		stream >> sourceId;

		for (int i = 0; i < 2; i++) {
			stream >> junk; // "gives" OR "and"
			stream >> which;
			stream >> junk;
			stream >> destinationType;
			stream >> targetId;
			if ("bot" == destinationType) {
				if ("low" == which) {
					lowTarget = targetId;
				} else {
					highTarget = targetId;
				}
			} else {
				if ("low" == which) {
					lowTarget = -1;
				} else {
					highTarget = -1;
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
			fullBot.giveLowValueTo(bot(connection->second.first));
			fullBot.giveHighValueTo(bot(connection->second.second));
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

private:
	std::map<int, Bot> bots;
	std::map<int, std::pair<int, int>> connections;
};
