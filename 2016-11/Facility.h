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
            return element + " " + itemClass();
        }

        void serialize(std::ostream& stream) const {
            stream << description();
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

    static std::shared_ptr<Item> createItem(std::istream& stream) {
        std::string element;
        std::string type;
        stream >> element >> type;
        if (std::string{"generator"} == type) {
            return std::make_shared<GeneratorItem>(element);
        } else if (std::string{"microchip"} == type) {
            return std::make_shared<MicrochipItem>(element);
        } else {
            assert(false);
        }
        return nullptr;
    }

    class Container;

    class Container {
    public:
        void takeItemsFrom(Container& otherContainer) {
            while (0 < otherContainer.count()) {
                addItem(otherContainer.removeItem(0));
            }
        }

        void addItem(std::shared_ptr<Item> item) {
            items.push_back(item);
            std::sort(items.begin(), items.end(), [](std::shared_ptr<Item> pa, std::shared_ptr<Item> pb) -> bool {
                Item& a = *pa;
                Item& b = *pb;
                if (a.element < b.element) {
                    return true;
                }
                if (a.element > b.element) {
                    return false;
                }
                if (a.itemClass() == std::string{"microchip"}) {
                    return true;
                }
                return false;
            });
        }

        bool validateContents() const {
            // For each unprotected microchip, is there a generator to fry it?
            bool anyUnprotectedMicrochips = false;
            bool anyGenerators = false;
            for (auto iter = items.begin(); items.end() != iter; ++iter) {
                auto item = *iter;
                if (item->itemClass() == "generator") {
                    anyGenerators = true;
                } else if (item->itemClass() == "microchip") {
                    auto iter_next = iter + 1;
                    if (iter_next == items.end()) {
                        anyUnprotectedMicrochips = true;
                    } else {
                        auto item_next = *iter_next;
                        if (item->element != item_next->element) {
                            anyUnprotectedMicrochips = true;
                        }
                    }
                } else {
                    assert(false);
                }
            }
            return !anyUnprotectedMicrochips || !anyGenerators;
        }

        std::shared_ptr<Item> removeItem(int index) {
            assert(index < items.size());
            std::shared_ptr<Item> removedItem;
            removedItem = items[index];
            items.erase(items.begin() + index);
            return removedItem;
        }

        int count() const {
            return items.size();
        }

        Item& item(int index) {
            return *(items[index]);
        }

        void serialize(std::ostream& stream) const {
            stream << items.size();
            for (const auto& item : items) {
                stream << " ";
                item->serialize(stream);
            }
            stream << std::endl;
        }

        void serialize(std::istream& stream) {
            int count;
            stream >> count;
            for (int i = 0; i < count; ++i) {
                addItem(createItem(stream));
            }
        }

    private:
        std::vector<std::shared_ptr<Item>> items;
    };

    class Facility {
    public:
        std::string serialize() const {
            std::stringstream stream;
            serialize(static_cast<std::ostream&>(stream));
            return stream.str();
        }

        void serialize(std::ostream& stream) const {
            stream << _elevatorFloor << std::endl;
            for (int floor = 1; floor <= _floors.size(); ++floor) {
                stream << floor << " ";
                _floors[floor - 1].serialize(stream);
            }
        }

        void serialize(std::istream& stream) {
            stream >> std::skipws >> _elevatorFloor;
            while (!stream.eof()) {
                int floorNumber;
                stream >> floorNumber;
                assert(floorNumber > 0);
                if (floorNumber > _floors.size()) {
                    _floors.resize(floorNumber);
                    _floors[floorNumber - 1].serialize(stream);
                }
            }
        }

        bool isLegal() const {
            if (!_elevator.validateContents()) {
                return false;
            }
            for (const auto& floor : _floors) {
                if (!floor.validateContents()) {
                    return false;
                }
            }
            return true;
        }

        bool isEndingMove() const {
            for (int i = 1; i < _floors.size(); ++i) {
                if (0 != _floors[i - 1].count()) {
                    return false;
                }
            }
            return true;
        }

        std::vector<Facility> moves() const {
            std::vector<Facility> moves;

            assert(0 == _elevator.count());

            for (int i = 0; i < _floors[_elevatorFloor - 1].count(); ++i) {
                Facility oneItemLoaded{*this};
                oneItemLoaded._elevator.addItem(oneItemLoaded._floors[_elevatorFloor - 1].removeItem(i));
                if (oneItemLoaded.isLegal()) {
                    if (_elevatorFloor > 1) {
                        Facility downOneFloor(oneItemLoaded);
                        --downOneFloor._elevatorFloor;
                        downOneFloor._floors[downOneFloor._elevatorFloor - 1].takeItemsFrom(downOneFloor._elevator);
                        if (downOneFloor.isLegal()) {
                            moves.push_back(downOneFloor);
                        }
                    }
                    if (_elevatorFloor < _floors.size()) {
                        Facility upOneFloor(oneItemLoaded);
                        ++upOneFloor._elevatorFloor;
                        upOneFloor._floors[upOneFloor._elevatorFloor - 1].takeItemsFrom(upOneFloor._elevator);
                        if (upOneFloor.isLegal()) {
                            moves.push_back(upOneFloor);
                        }
                    }
                }
                for (int j = 0; j < oneItemLoaded._floors[_elevatorFloor - 1].count(); j++) {
                    Facility twoItemsLoaded{oneItemLoaded};
                    twoItemsLoaded._elevator.addItem(twoItemsLoaded._floors[_elevatorFloor - 1].removeItem(j));
                    if (twoItemsLoaded.isLegal()) {
                        if (_elevatorFloor > 1) {
                            Facility downOneFloor(twoItemsLoaded);
                            --downOneFloor._elevatorFloor;
                            downOneFloor._floors[downOneFloor._elevatorFloor - 1].takeItemsFrom(downOneFloor._elevator);
                            if (downOneFloor.isLegal()) {
                                moves.push_back(downOneFloor);
                            }
                        }
                        if (_elevatorFloor < _floors.size()) {
                            Facility upOneFloor(twoItemsLoaded);
                            ++upOneFloor._elevatorFloor;
                            upOneFloor._floors[upOneFloor._elevatorFloor - 1].takeItemsFrom(upOneFloor._elevator);
                            if (upOneFloor.isLegal()) {
                                moves.push_back(upOneFloor);
                            }
                        }
                    }
                }
            }

            return moves;
        }

    private:
        using Floors = std::vector<Container>;

        int _elevatorFloor{-1};
        Floors _floors;
        Container _elevator;
    };
}
