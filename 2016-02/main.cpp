#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>

class Key {
public:
    const char up;
    const char left;
    const char right;
    const char down;

    Key(char up, char left, char right, char down) : up{up}, left{left}, right{right}, down{down} {
    }

    char move(char direction) const {
        switch (direction) {
            case 'U':
                return up;
                break;
            case 'L':
                return left;
                break;
            case 'R':
                return right;
                break;
            case 'D':
                return down;
                break;
        }
        throw std::exception();
    }
};

class Keypad {
public:
    char move(char direction) {
        currentKey = keys.find(currentKey)->second.move(direction);
        return currentKey;
    }

    char current() const {
        return currentKey;
    }

protected:
    std::unordered_map<char, Key> keys;
    char currentKey{'5'};
};

class NormalKeypad : public Keypad {
public:
    NormalKeypad() {
        //           KEY       UP  LFT  RGT  DWN
        keys.emplace('1', Key{'1', '1', '2', '4'});
        keys.emplace('2', Key{'2', '1', '3', '5'});
        keys.emplace('3', Key{'3', '2', '3', '6'});
        keys.emplace('4', Key{'1', '4', '5', '7'});
        keys.emplace('5', Key{'2', '4', '6', '8'});
        keys.emplace('6', Key{'3', '5', '6', '9'});
        keys.emplace('7', Key{'4', '7', '8', '7'});
        keys.emplace('8', Key{'5', '7', '9', '8'});
        keys.emplace('9', Key{'6', '8', '9', '9'});
    }
};

class CrazyKeypad : public Keypad {
public:
    CrazyKeypad() {
        //           KEY       UP  LFT  RGT  DWN
        keys.emplace('1', Key{'1', '1', '1', '3'});
        keys.emplace('2', Key{'2', '2', '3', '6'});
        keys.emplace('3', Key{'1', '2', '4', '7'});
        keys.emplace('4', Key{'4', '3', '4', '8'});
        keys.emplace('5', Key{'5', '5', '6', '5'});
        keys.emplace('6', Key{'2', '5', '7', 'A'});
        keys.emplace('7', Key{'3', '6', '8', 'B'});
        keys.emplace('8', Key{'4', '7', '9', 'C'});
        keys.emplace('9', Key{'9', '8', '9', '9'});
        keys.emplace('A', Key{'6', 'A', 'B', 'A'});
        keys.emplace('B', Key{'7', 'A', 'C', 'D'});
        keys.emplace('C', Key{'8', 'B', 'C', 'C'});
        keys.emplace('D', Key{'B', 'D', 'D', 'D'});
    }
};

int main(int argc, const char* argv[]) {
    bool part2 = (argc > 1 && '2' == argv[1][0]);
    std::ifstream input("input");
    std::string line;
    std::unique_ptr<Keypad> keypad;
    if (part2) {
        keypad.reset(new CrazyKeypad);
    } else {
        keypad.reset(new NormalKeypad);
    }
    while (std::getline(input, line)) {
        for (auto move : line) {
            keypad->move(move);
        }
        std::cout << keypad->current();
    }
    std::cout << std::endl;
    return 0;
}
