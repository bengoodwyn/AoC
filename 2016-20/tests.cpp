#include <memory>
#include <sstream>
#include <gtest/gtest.h>

#include <tuple>
#include <vector>

namespace AoC {
    class FirewallRules {
    public:
        using Rule = std::pair<uint64_t, uint64_t>;

        void addRule(uint64_t start, uint64_t end) {
            rules.push_back({start, end});
        }

        uint64_t lowestUnblockedAddress() {
            uint64_t address = 0;
            while (true) {
                bool blocked = false;
                for (auto rule : rules) {
                    if (address >= rule.first && address <= rule.second) {
                        blocked = true;
                        break;
                    }
                }
                if (blocked) {
                    ++address;
                } else {
                    return address;
                }
            }
        }

    private:
        std::vector<Rule> rules;
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
