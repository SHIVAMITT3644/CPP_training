#include <gtest/gtest.h>
#include <gmock/gmock.h>

MATCHER_P(IsDivisibleBy, n, " it must be divisible by 4") {
    *result_listener << "where the remainder is " << (arg % n);
    return (arg % n) == 0;
}

TEST(TestDivisible, Example) {
    EXPECT_THAT(16, IsDivisibleBy(4));
}