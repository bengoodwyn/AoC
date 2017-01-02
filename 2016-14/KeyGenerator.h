#include <array>
#include <cstdio>
#include <string>
#include <map>
#include <openssl/md5.h>

namespace AoC {
    class KeyGenerator {
    public:
        KeyGenerator(std::string salt) : salt(salt) {
        }

        std::string saltInteger(int integer) {
            return salt + std::to_string(integer);
        }

        const char* digest(std::string input) {
            static unsigned char digest[16];
            static std::array<char, (sizeof(digest) * 2) + 1> strDigest;
            MD5(reinterpret_cast<const unsigned char*>(input.data()), input.length(), digest);
            snprintf(&strDigest.at(0), strDigest.size(),
                "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x", digest[0], digest[1], digest[2],
                digest[3], digest[4], digest[5], digest[6], digest[7], digest[8], digest[9], digest[10], digest[11],
                digest[12], digest[13], digest[14], digest[15]);
            return &strDigest.at(0);
        }

        char findTriple(std::string input) {
            int repeatCount = 0;
            char repeatChar = '\0';
            for (auto current : input) {
                if (current == repeatChar) {
                    if (3 == ++repeatCount) {
                        return repeatChar;
                    }
                } else {
                    repeatChar = current;
                    repeatCount = 1;
                }
            }
            return '\0';
        }

        bool findQuintuple(std::string input, char character) {
            std::string needle(5, character);
            return std::string::npos != input.find(needle);
        }

        int indexOfKey(int keyCount) {
            int index = 0;
            int numberOfFoundKeys = 0;
            int indexOfDesiredKey = -1;
            std::map<int, char> watchingForQuintuples;
            while (-1 == indexOfDesiredKey) {
                std::string possibleKey = digest(saltInteger(index));
                char triple = findTriple(possibleKey);
                if (triple != '\0') {
                    //std::cerr << "index " << index << " has triple " << triple << " " << possibleKey << std::endl;
                    watchingForQuintuples[index] = triple;
                }
                for (auto quintWatch : watchingForQuintuples) {
                    if ((quintWatch.first < index) && findQuintuple(possibleKey, quintWatch.second)) {
                        //std::cerr << "index " << quintWatch.first << " was a key because of " << quintWatch.second << " (" << index << ")" << std::endl;
                        if (keyCount == ++numberOfFoundKeys) {
                            indexOfDesiredKey = quintWatch.first;
                        }
                    }
                }
                if (index >= 1000) {
                    watchingForQuintuples.erase(index - 1000);
                }
                ++index;
            }
            return indexOfDesiredKey;
        }

    private:
        std::string salt;
    };
}
