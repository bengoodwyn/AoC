#pragma once

#include <iostream>

class Value {
public:
	Value()
		: value{-1} {
	}

	Value(int value)
		: value{value} {
	}

	int value;
};

class Bot {
public:
	void receive(Value value) {
	}

	Value takeHighValue() {
		return Value(200);
	}

};

class Output {

};

class Factory {

};
