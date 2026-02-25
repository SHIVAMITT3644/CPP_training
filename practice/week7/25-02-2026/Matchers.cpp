#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(MatcherTest, BasicExpectThat)
{
    EXPECT_THAT(1, testing::Eq(1));
    EXPECT_THAT(0, 2-2);
    EXPECT_THAT(1-1, 0);
    EXPECT_THAT(2*2, 4);
}

TEST(MatcherTest, UsingMatchers)
{
    testing::Matcher<int> is_one = 1;
    testing::Matcher<int> is_zero = 0;
    testing::Matcher<bool> is_true = true;

    EXPECT_THAT(1, is_one);
    EXPECT_THAT(2-2, is_zero);
    EXPECT_THAT(1-1, is_zero);
    EXPECT_THAT(1==1, is_true);
}
