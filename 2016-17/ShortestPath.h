#include <array>
#include <string>
#include <tuple>
#include <vector>
#include <openssl/md5.h>

namespace AoC {
    class ShortestPath {
    public:
        constexpr static int width = 4;
        constexpr static int height = 4;
        using Coordinates = std::pair<int, int>;
        using Position = std::pair<Coordinates, std::string>;

        static std::string find(std::string passcode) {
            const Coordinates desiredPosition{width - 1, height - 1};
            const Coordinates startingPosition{0, 0};
            std::vector<Position> exploredPositions;
            exploredPositions.push_back({startingPosition, passcode});
            while (true) {
                assert(exploredPositions.size() > 0);
                std::vector<Position> possiblePositions;
                for (auto position : exploredPositions) {
                    auto newlyExploredPositions = explore(position);
                    for (auto newlyExploredPosition : newlyExploredPositions) {
                        //std::cerr << newlyExploredPosition.first.first << "," << newlyExploredPosition.first.second
                        //    << " " << newlyExploredPosition.second << std::endl;
                        if (newlyExploredPosition.first == desiredPosition) {
                            return newlyExploredPosition.second.substr(passcode.length());
                        }
                        possiblePositions.push_back(newlyExploredPosition);
                    }
                }
                exploredPositions = possiblePositions;
            }
        }

        static const char* digest(std::string input) {
            static unsigned char digest[16];
            static std::array<char, 4 + 1> strDigest;
            MD5(reinterpret_cast<const unsigned char*>(input.data()), input.length(), digest);
            snprintf(&strDigest.at(0), strDigest.size(), "%02x%02x", digest[0], digest[1]);
            return &strDigest.at(0);
        }

        static std::vector<Position> explore(Position position) {
            std::vector<Position> positions;
            std::string partialMd5 = digest(position.second);
            assert(4 == partialMd5.length());
            if ('a' < partialMd5.at(0) && position.first.second > 0) {
                Position newPosition = position;
                --newPosition.first.second;
                newPosition.second += 'U';
                positions.push_back(newPosition);
            }
            if ('a' < partialMd5.at(1) && position.first.second < (height - 1)) {
                Position newPosition = position;
                ++newPosition.first.second;
                newPosition.second += 'D';
                positions.push_back(newPosition);
            }
            if ('a' < partialMd5.at(2) && position.first.first > 0) {
                Position newPosition = position;
                --newPosition.first.first;
                newPosition.second += 'L';
                positions.push_back(newPosition);
            }
            if ('a' < partialMd5.at(3) && position.first.first < (width - 1)) {
                Position newPosition = position;
                ++newPosition.first.first;
                newPosition.second += 'R';
                positions.push_back(newPosition);
            }
            return positions;
        }
    };
}
