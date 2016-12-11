#pragma once

#include <array>

namespace AoC {
    namespace Year2016Day01 {

        template<class T> class Boxed {
        public:
            Boxed(T value = 0) : value{value} {
            }

            operator T() const {
                return value;
            }

            Boxed& operator=(const Boxed& rhs) {
                value = rhs.value;
                return *this;
            }

        protected:
            T value;
        };

        class Turn : public Boxed<int> {
        public:
            Turn(int value) : Boxed(value) {

            }

            static constexpr int Right() {
                return 0;
            };

            static constexpr int Left() {
                return 1;
            };

            static constexpr size_t Count() {
                return 2;
            };
        };

        class Facing : public Boxed<int> {
        public:
            Facing(int value) : Boxed(value) {
            }

            Facing turn(Turn turn) {
                switch (turn) {
                    case Turn::Right():
                        return right();
                    case Turn::Left():
                        return left();
                }
                return *this;
            }

            Facing right() const {
                return (value + 1) % Count();
            }

            Facing left() const {
                return (value + 3) % Count();
            }

            static constexpr int North() {
                return 0;
            }

            static constexpr int East() {
                return 1;
            }

            static constexpr int South() {
                return 2;
            }

            static constexpr int West() {
                return 3;
            }

            static constexpr int Count() {
                return 4;
            }

            static constexpr int Default() {
                return North();
            }
        };

        class MapTraveler {
        public:
            using Position = std::pair<int, int>;

            void turn(Turn turn) {
                facing = facing.turn(turn);
            }

            void travel(int distance) {
                switch (facing) {
                    case Facing::North():
                        position.second += distance;
                        break;
                    case Facing::East():
                        position.first += distance;
                        break;
                    case Facing::South():
                        position.second -= distance;
                        break;
                    case Facing::West():
                        position.first -= distance;
                        break;
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
            Facing facing{Facing::Default()};
        };
    }
}
