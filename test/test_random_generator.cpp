
#include <gtest/gtest.h>
#include "rand_generator.hpp"
TEST(testMath, myCubeTest)
{
    EXPECT_EQ(1000, 1000);

    auto randomInt = RandomGenerator<int>::generate();
    auto randomString = RandomGenerator<std::string>::generate();
    auto randomVector = RandomGenerator<std::vector<int>>::generate();
    auto randomMap = RandomGenerator<std::map<int, std::string>>::generate();
    auto randomTuple = RandomGenerator<std::tuple<int, double, std::string>>::generate();
}
