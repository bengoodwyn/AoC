#pragma once

using Value = std::uint64_t;

class ValueReceiver {
public:
    const int id;

    ValueReceiver(int id) : id{id} {
    }

    virtual void receive(Value value) = 0;
};
