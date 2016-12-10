#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <array>

class Key {
public:
    char up;
    char left;
    char right;
    char down;

    Key() : up(0), left(0), right(0), down(0) {
    }

    Key(char up, char left, char right, char down) : up(up), left(left), right(right), down(down) {
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
    Keypad() : currentKey('5') {
        // 				 UP  LFT  RGT  DWN
        keys['1'] = Key('1', '1', '1', '3');
        keys['2'] = Key('2', '2', '3', '6');
        keys['3'] = Key('1', '2', '4', '7');
        keys['4'] = Key('4', '3', '4', '8');
        keys['5'] = Key('5', '5', '6', '5');
        keys['6'] = Key('2', '5', '7', 'A');
        keys['7'] = Key('3', '6', '8', 'B');
        keys['8'] = Key('4', '7', '9', 'C');
        keys['9'] = Key('9', '8', '9', '9');
        keys['A'] = Key('6', 'A', 'B', 'A');
        keys['B'] = Key('7', 'A', 'C', 'D');
        keys['C'] = Key('8', 'B', 'C', 'C');
        keys['D'] = Key('B', 'D', 'D', 'D');
    };

    char move(char direction) {
        currentKey = keys[currentKey].move(direction);
        return currentKey;
    }

    char current() const {
        return currentKey;
    }

private:
    std::array<Key, 256> keys;
    char currentKey;
};

int main() {
    std::ifstream input("input");
    std::string line;
    Keypad keypad;
    while (std::getline(input, line)) {
        for (auto move : line) {
            keypad.move(move);
        }
        std::cout << keypad.current() << std::endl;
    }
    return 0;
}
