#pragma once

#include <list>

namespace AoC {
    class ElfGame {
    public:
        using Elf = int;

        static int play(int count) {
            std::list<Elf> elves;
            for (int i = 0; i < count; ++i) {
                elves.push_back(i + 1);
            }
            auto current = elves.begin();
            while (elves.size() > 1) {
                auto next = std::next(current);
                if (elves.end() == next) {
                    next = elves.begin();
                }
                auto deleteAt = next;
                next = std::next(next);
                elves.erase(deleteAt);
                if (elves.end() == next) {
                    next = elves.begin();
                }
                current = next;
            }
            return elves.front();
        }
    };
}
