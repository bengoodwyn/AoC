#pragma once

#include <iostream>
#include <list>

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

};
