#pragma once

#include <cassert>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

namespace AoC {
    class Item {
    public:
        Item(std::string element) : element{element} {
        }

        virtual std::string itemClass() const = 0;

        const std::string element;

        std::string description() const {
            return element + ":" + itemClass();
        }
    };

    class GeneratorItem : public Item {
    public:
        GeneratorItem(std::string element) : Item{element} {
        }

        virtual std::string itemClass() const override {
            return "generator";
        }
    };

    class MicrochipItem : public Item {
    public:
        MicrochipItem(std::string element) : Item{element} {
        }

        virtual std::string itemClass() const override {
            return "microchip";
        }
    };

    class Container;

    class Container {
    public:
        void takeItemsFrom(Container& otherContainer) {
            while (0 < otherContainer.count()) {
                addItem(otherContainer.removeItem(0));
            }
        }

        void addItem(std::unique_ptr<Item> item) {
            items.emplace_back(std::move(item));
        }

        bool validateContents() const {
            return true;
        }

        std::unique_ptr<Item> removeItem(int index) {
            std::unique_ptr<Item> removedItem;
            removedItem = std::move(items[index]);
            items.erase(items.begin() + index);
            return removedItem;
        }

        int count() const {
            return items.size();
        }

        Item& item(int index) {
            return *(items[index]);
        }

    private:
        std::vector<std::unique_ptr<Item>> items;
    };

    class Elevator {
    public:
        static constexpr int capacity() {
            return 2;
        }

        class OverCapacity {
        };

        class Empty {
        };

        int currentFloor() const {
            return floor;
        }

        void up() {
            if (items.count() > 2) {
                throw OverCapacity();
            }
            if (0 == items.count()) {
                throw Empty();
            }
            assert(floor < floorCount);
            ++floor;
        }

        void down() {
            if (items.count() > 2) {
                throw OverCapacity();
            }
            if (0 == items.count()) {
                throw Empty();
            }
            assert(floor > 1);
            --floor;
        }

        int floors() const {
            return floorCount;
        }

        void setFloors(int floors) {
            floorCount = floors;
            assert(floor <= floorCount);
        }

        Container items;

    private:
        int floor{1};
        int floorCount{0};
    };

    class Facility {
    public:
        void addFloor(std::string floor) {
            std::cerr << floor << std::endl;
            std::stringstream stream(floor);
            int floorNumber;
            stream >> floorNumber;
            assert(floorNumber > 0);
            if (floorNumber > _elevator.floors()) {
                _elevator.setFloors(floorNumber);
                _floors.resize(floorNumber);
            }
        }

        int floors() const {
            assert(_floors.size() == _elevator.floors());
            return _elevator.floors();
        }

        Elevator& elevator() {
            return _elevator;
        }

    private:
        using Floors = std::vector<Container>;
        Elevator _elevator;
        Floors _floors;
    };
}
