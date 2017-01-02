#pragma once

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

        uint64_t lowestUnblockedAddress() {
            uint64_t address = 0;
            for (auto rule : rules) {
                std::cerr << rule.first << "-" << rule.second << std::endl;
                if (address >= rule.first && address <= rule.second) {
                    address = std::max(rule.second + 1, address);
                }
            }
            return address;
        }

    private:
        std::map<uint64_t, uint64_t> rules;
    };
}
