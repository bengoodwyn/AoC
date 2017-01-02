#include <cctype>
#include <iostream>
#include <vector>

namespace AoC {
    class Sculpture {
    public:
        Sculpture(std::istream& stream) {
            int size, initial;
            while (!stream.eof()) {
                stream >> size >> initial;
                discs.push_back({size, initial});
                while (!stream.eof() && std::isspace(stream.peek())) {
                    stream.get();
                }
            }
        }

        int execute() {
            int dropped_at = 0;
            while (true) {
                if (test_disc(dropped_at)) {
                    return dropped_at;
                }
                ++dropped_at;
            }
        }

    private:
        bool test_disc(int dropped_at) {
            int delta_t = 0;
            for (auto disc : discs) {
                ++delta_t;
                if (0 != ((dropped_at + delta_t + disc.second) % disc.first)) {
                    return false;
                }
            }
            return true;
        }

        std::vector<std::pair<int, int>> discs;
    };
}
