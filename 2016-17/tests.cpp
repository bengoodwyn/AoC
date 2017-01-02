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

TEST(ShortestPathTest, SampleTest1Long) {
    ASSERT_EQ(370, ShortestPath::find("ihgpwlah", ShortestPath::PathType::Longest).length());
}

TEST(ShortestPathTest, SampleTest2Long) {
    ASSERT_EQ(492, ShortestPath::find("kglvqrro", ShortestPath::PathType::Longest).length());
}

TEST(ShortestPathTest, SampleTest3Long) {
    ASSERT_EQ(830, ShortestPath::find("ulqzkmiv", ShortestPath::PathType::Longest).length());
}
