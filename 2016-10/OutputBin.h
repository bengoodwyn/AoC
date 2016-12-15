#pragma once

#include "ValueReceiver.h"

class OutputBin : public ValueReceiver {
public:
    OutputBin(int id) : ValueReceiver{id} {
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

