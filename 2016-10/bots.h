#pragma once

#include <iostream>
#include <list>

using Value = std::uint64_t;

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

	Value takeLowValue() {
		auto value = values.front();
		values.pop_front();
		return value;
	}

private:
	std::list<Value> values;
};

class Output {

};

class Factory {

};
