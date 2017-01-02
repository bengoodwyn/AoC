#include <cassert>
#include <string>

namespace AoC {
    class Dragon {
    public:
        static std::string expand(std::string a) {
            std::string result = a + '0';
            for (auto iter = a.rbegin(); a.rend() != iter; iter++) {
                if (*iter == '0') {
                    result += '1';
                } else if (*iter == '1') {
                    result += '0';
                } else {
                    assert(false);
                }
            }
            return result;
        }

        static std::string generate(std::string initial, int length) {
            std::string result = initial;
            while (result.length() < length) {
                result = expand(result);
            }
            return result.substr(0, length);
        }

        static std::string checksum(std::string input) {
            std::string result;
            for (int i = 0; i < input.length(); i += 2) {
                if (input.at(i) == input.at(i + 1)) {
                    result += '1';
                } else {
                    result += '0';
                }
            }
            if (0 == (result.length() % 2)) {
                return checksum(result);
            } else {
                return result;
            }
        }
    };
}
