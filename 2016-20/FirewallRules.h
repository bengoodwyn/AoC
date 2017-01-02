#pragma once

#include <cassert>
#include <cstdint>
#include <map>

namespace AoC {
    class FirewallRules {
    public:
        void addRule(uint64_t start, uint64_t end) {
            auto iter = rules.find(start);
            if (rules.end() != iter) {
                iter->second = std::max(iter->second, end);
            } else {
                rules.insert({start, end});
            }
        }

        uint64_t countUnblockedAddresses() {
            uint64_t start = lowestUnblockedAddress();
            uint64_t end = lowestBlockedAddress(start) - 1;
            assert(end >= start);
            uint64_t count = (end - start + 1);
            while (start < 4294967296 && end < 4294967296) {
                start = lowestUnblockedAddress(end + 1);
                end = lowestBlockedAddress(start) - 1;
                count += (end - start + 1);
            }
            return count;
        }

        uint64_t lowestUnblockedAddress(uint64_t startingWith = 0) {
            uint64_t address = startingWith;
            for (auto rule : rules) {
                if (address >= rule.first && address <= rule.second) {
                    address = std::max(rule.second + 1, address);
                }
            }
            return address;
        }

        uint64_t lowestBlockedAddress(uint64_t startingWith) {
            uint64_t address = startingWith;
            for (auto rule : rules) {
                if (address >= rule.first && address <= rule.second) {
                    return address;
                } else if (address < rule.first) {
                    return rule.first;
                }
            }
            return 4294967296;
        }

    private:
        std::map<uint64_t, uint64_t> rules;
    };
}
