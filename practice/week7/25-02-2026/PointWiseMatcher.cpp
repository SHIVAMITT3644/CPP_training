#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

using namespace testing;

TEST(ContainerMatchersExample, AllInOne) {
    std::vector<int> actual   = {2, 4, 6, 8};
    std::vector<int> expected = {1, 2, 3, 4};

    EXPECT_THAT(actual, Contains(6));
    EXPECT_THAT(actual, ElementsAre(2, 4, 6, 8));
    EXPECT_THAT(actual, Pointwise(Eq(), expected));
}
