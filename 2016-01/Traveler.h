#pragma once

#include <array>

namespace AoC {
    enum class Turn {
        Left, Right
    };

    enum class Facing {
        North = 0, East, South, West, Count
    };

    class Traveler;

    class Traveler {
    public:
        class Follower {
        public:
            virtual void onTravelerMoved(Traveler& traveler) = 0;
        };

        void addFollower(Follower& follower) {
            followers.insert(&follower);
        }

        using Position = std::pair<int, int>;

        void turn(Turn turn) {
            switch (turn) {
                case Turn::Right:
                    facing = static_cast<Facing>((static_cast<int>(facing) + 1) % static_cast<int>(Facing::Count));
                    break;
                case Turn::Left:
                    facing = static_cast<Facing>((static_cast<int>(facing) + 3) % static_cast<int>(Facing::Count));
                    break;
            }
        }

        void travel(int distance) {
            switch (facing) {
                case Facing::North:
                    position.second += distance;
                    break;
                case Facing::East:
                    position.first += distance;
                    break;
                case Facing::South:
                    position.second -= distance;
                    break;
                case Facing::West:
                    position.first -= distance;
                    break;
                default:
                    assert(false);
            }
            for (auto follower : followers) {
                follower->onTravelerMoved(*this);
            }
        }

        Position currentPosition() const {
            return position;
        }

        Facing currentFacing() const {
            return facing;
        }

        int distanceFromOrigin() const {
            return std::abs(position.first) + std::abs(position.second);
        }

    private:
        Position position{0, 0};
        Facing facing{Facing::North};
        std::set<Follower*> followers;
    };
}
