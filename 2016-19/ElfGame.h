#pragma once

#include <functional>
#include <list>

namespace AoC {
    class ElfGame {
    public:
        using Elf = int;

        static int play(int count, std::function<int(int, int)> targetingFunction) {
            std::list<Elf> elves;
            for (int i = 0; i < count; ++i) {
                elves.push_back(i + 1);
            }
            auto current = elves.begin();
            int currentIndex = 0;
            auto cache = current;
            int cacheIndex = currentIndex;
            while (elves.size() > 1) {
                int targetIndex = targetingFunction(currentIndex, elves.size());
                auto target = current;
                if (targetIndex > cacheIndex) {
                    target = std::next(cache, targetIndex - cacheIndex);
                } else if (cacheIndex > targetIndex) {
                    target = std::prev(cache, cacheIndex - targetIndex);
                } else {
                    target = cache;
                }
                if (targetIndex == (currentIndex + 1)) {
                    current = std::next(current, 2);
                } else {
                    current = std::next(current, 1);
                }
                if (target == elves.begin()) {
                    cache = std::prev(elves.end());
                    cacheIndex = elves.size() - 1;
                } else {
                    cache = std::prev(target);
                    cacheIndex = targetIndex - 1;
                }
                elves.erase(target);
                if (targetIndex > currentIndex) {
                    ++currentIndex;
                }
                if (cacheIndex > targetIndex) {
                    --cacheIndex;
                }
                if (elves.end() == current) {
                    current = elves.begin();
                    currentIndex = 0;
                }
            }
            return elves.front();
        }
    };
}
