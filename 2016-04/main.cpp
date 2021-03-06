#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <array>
#include <map>
#include <list>
#include <set>
#include <sstream>

std::list<std::string> breakLineByDashes(std::string line) {
    std::list<std::string> components;
    std::stringstream lineStream(line);
    std::string component;
    while (std::getline(lineStream, component, '-')) {
        components.push_back(component);
    }
    return components;
}

std::string calculateChecksum(std::list<std::string> components) {
    std::string checksum;
    std::map<char, int> charFrequencies;
    for (auto component : components) {
        for (auto character : component) {
            charFrequencies[character] += 1;
        }
    }
    std::map<int, std::set<char>, std::greater<int>> reverseCharFrequencies;
    for (auto frequency : charFrequencies) {
        //std::cout << frequency.second << frequency.first << " ";
        reverseCharFrequencies[frequency.second].insert(frequency.first);
    }
    //std::cout << std::endl;
    for (auto reverseFrequency : reverseCharFrequencies) {
        for (auto character : reverseFrequency.second) {
            //std::cout << reverseFrequency.first << character;
            if (checksum.length() < 5) {
                checksum += character;
            }
        }
    }
    //std::cout << std::endl;
    return checksum;
}

int extractValue(std::string component) {
    auto len = component.find('[');
    return std::stoi(component.substr(0, len));
}

std::string extractChecksum(std::string component) {
    auto start = component.find('[') + 1;
    auto end = component.find(']');
    return component.substr(start, end - start);
}

std::string decryptRoom(std::list<std::string> components, int key) {
    std::string room;
    for (auto component : components) {
        if (!room.empty()) {
            room += ' ';
        }
        for (auto character : component) {
            room += 'a' + (((character - 'a') + key) % 26);
        }
    }
    return room;
}

std::pair<int, std::string> processRoomLine(std::string line) {
    std::pair<int, std::string> result;
    //std::cout << line << std::endl;
    auto components = breakLineByDashes(line);
    auto lastComponent = *components.rbegin();
    auto testChecksum = extractChecksum(lastComponent);
    components.pop_back();
    auto calcChecksum = calculateChecksum(components);
    if (testChecksum == calcChecksum) {
        auto key = extractValue(lastComponent);
        result = std::make_pair(key, decryptRoom(components, key));
    } else {
        //std::cout << calcChecksum << " " << testChecksum << std::endl;
    }
    return result;
}

int main(int argc, const char* argv[]) {
    std::ifstream input("input");
    std::string line;
    while (std::getline(input, line)) {
        auto result = processRoomLine(line);
        if (result.first) {
            if (argc > 1 && -1 != result.second.find(argv[1])) {
                std::cout << "****** ";
            }
            std::cout << result.first << " " << result.second << std::endl;
        }
    }
    return 0;
}
