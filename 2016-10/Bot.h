#pragma once

#include <iostream>
#include <functional>
#include <tuple>

#include "ValueReceiver.h"

class Bot : public ValueReceiver {
public:
    using Comparator = std::function<bool(int, Value, Value)>;

    static Comparator DefaultComparator;

    Bot(int id, Comparator comparator = DefaultComparator) : ValueReceiver{id}, comparator{comparator} {
    }

    virtual void receive(Value value) override {
        if (0 == values.first) {
            values.first = value;
        } else if (comparator(id, value, values.first)) {
            std::swap(values.first, values.second);
            values.first = value;
        } else {
            values.second = value;
        }
        possiblyGiveValuesThroughConnection();
    }

    void connectTo(ValueReceiver* lowReceiver, ValueReceiver* highReceiver) {
        connections.first = lowReceiver;
        connections.second = highReceiver;
        possiblyGiveValuesThroughConnection();
    }

private:
    void possiblyGiveValuesThroughConnection() {
        if (connections.first && connections.second && values.first && values.second) {
            connections.first->receive(values.first);
            connections.second->receive(values.second);
            values.first = 0;
            values.second = 0;
        }
    }

    Comparator comparator;
    std::pair<Value, Value> values;
    std::pair<ValueReceiver*, ValueReceiver*> connections;
};
