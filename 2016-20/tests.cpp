#include <memory>
#include <sstream>
#include <gtest/gtest.h>

#include <tuple>
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
                if (address >= rule.first && address <= rule.second) {
                    address = std::max(rule.second + 1, address);
                } else {
                    return address;
                }
            }
            return address;
        }

    private:
        std::map<uint64_t, uint64_t> rules;
    };
}

using namespace AoC;

class FirewallRulesTest : public ::testing::Test {
public:
    virtual void SetUp() override {
        firewallRules.reset(new FirewallRules());
    }

    virtual void TearDown() override {
        firewallRules.reset();
    }

    std::unique_ptr<FirewallRules> firewallRules;
};

TEST_F(FirewallRulesTest, CanAddRuleToFirewall) {
    firewallRules->addRule(0, 10);
}

TEST_F(FirewallRulesTest, CanFindLowestUnblockedAddress) {
    ASSERT_EQ(0, firewallRules->lowestUnblockedAddress());
}

TEST_F(FirewallRulesTest, CanFindLowestUnblockedAddressWithOneRule) {
    firewallRules->addRule(0, 10);
    ASSERT_EQ(11, firewallRules->lowestUnblockedAddress());
}

TEST_F(FirewallRulesTest, CanFindLowestUnblockedAddressWithTwoOverlappingRules) {
    firewallRules->addRule(0, 10);
    firewallRules->addRule(5, 15);
    ASSERT_EQ(16, firewallRules->lowestUnblockedAddress());
}

TEST_F(FirewallRulesTest, CanFindLowestUnblockedAddressWithTwoContiguousRules) {
    firewallRules->addRule(0, 10);
    firewallRules->addRule(11, 20);
    ASSERT_EQ(21, firewallRules->lowestUnblockedAddress());
}

TEST_F(FirewallRulesTest, CanFindLowestUnblockedAddressWithTwoDisjointRules) {
    firewallRules->addRule(0, 10);
    firewallRules->addRule(12, 20);
    ASSERT_EQ(11, firewallRules->lowestUnblockedAddress());
}
