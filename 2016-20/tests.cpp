#include <memory>
#include <sstream>
#include <gtest/gtest.h>

namespace AoC {
    class FirewallRules {
    public:
        void addRule(uint64_t start, uint64_t end) {
        }
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
