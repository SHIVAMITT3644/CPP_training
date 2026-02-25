#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(StringMatcher , matcherAllTest)
{
    std::string test("Hello ,this is test string,we are here to help!");
    
    EXPECT_THAT(test, testing::StartsWith("Hello"));
    EXPECT_THAT(test, testing::MatchesRegex(".*is.*help.*"));

    int number = 10;
    EXPECT_THAT(number , testing::AllOf(testing::Lt(100),testing::Gt(1),testing::Eq(10)));
}