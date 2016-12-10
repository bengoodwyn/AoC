#include <cassert>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <array>
#include <map>
#include <list>
#include <set>
#include <sstream>
#include <vector>
#include <limits>

bool processLine_TLS(std::string line) {
    int hypernet_count = 0;
    int abba_count_good = 0;
    int abba_count_bad = 0;
    for (int start = 0; start <= (line.length() - 4); ++start) {
        if ((std::string::npos == line.substr(start, 4).find('[')) &&
            (std::string::npos == line.substr(start, 4).find(']'))) {
            if (line.at(start) == line.at(start + 3) && line.at(start + 1) == line.at(start + 2)) {
                if (line.at(start) != line.at(start + 1)) {
                    if (0 == hypernet_count) {
                        ++abba_count_good;
                    } else {
                        ++abba_count_bad;
                    }
                }
            }
        }
        if (line.at(start) == '[') {
            ++hypernet_count;
        } else if (line.at(start) == ']') {
            --hypernet_count;
            assert(hypernet_count >= 0);
        }
    }
    return abba_count_good > 0 && 0 == abba_count_bad;
}

bool processLine_SSL(std::string line) {
    int hypernet_count = 0;
    std::set<std::string> abas;
    std::set<std::string> babs;
    for (int start = 0; start <= (line.length() - 3); ++start) {
        if ((std::string::npos == line.substr(start, 3).find('[')) &&
            (std::string::npos == line.substr(start, 3).find(']'))) {
            if (line.at(start) == line.at(start + 2) && line.at(start) != line.at(start + 1)) {
                if (0 == hypernet_count) {
                    abas.insert(line.substr(start, 2));
                } else {
                    babs.insert(line.substr(start, 2));
                }
            }
        }
        if (line.at(start) == '[') {
            ++hypernet_count;
        } else if (line.at(start) == ']') {
            --hypernet_count;
            assert(hypernet_count >= 0);
        }
    }
    for (auto aba : abas) {
        if (babs.end() != babs.find(aba.substr(1, 1) + aba.substr(0, 1))) {
            return true;
        }
    }
    return false;
}

int main(int argc, const char* argv[]) {
    std::ifstream input("input");
    std::string line;
    int count_TLS = 0;
    int count_SSL = 0;
    while (std::getline(input, line)) {
        if (processLine_TLS(line)) {
            ++count_TLS;
        }
        if (processLine_SSL(line)) {
            ++count_SSL;
        }
    }
    std::cout << count_TLS << " " << count_SSL << std::endl;
    return 0;
}
