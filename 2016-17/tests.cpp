#include <memory>
#include <sstream>
#include <gtest/gtest.h>

#include "ShortestPath.h"

using namespace AoC;

TEST(ShortestPathTest, SampleTest1) {
    ASSERT_EQ("DDRRRD", ShortestPath::find("ihgpwlah"));
}

TEST(ShortestPathTest, SampleTest2) {
    ASSERT_EQ("DDUDRLRRUDRD", ShortestPath::find("kglvqrro"));
}

TEST(ShortestPathTest, SampleTest3) {
    ASSERT_EQ("DRURDRUDDLLDLUURRDULRLDUUDDDRR", ShortestPath::find("ulqzkmiv"));
}
