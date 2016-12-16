#pragma once

#include "Value.h"

class ValueReceiver {
public:
    const int id;

    ValueReceiver(int id) : id{id} {
    }

    virtual void receive(Value value) = 0;
};
