#include "Bot.h"

Bot::Comparator Bot::DefaultComparator = [](int id, Value smaller, Value larger) -> bool {
    return smaller < larger;
};
