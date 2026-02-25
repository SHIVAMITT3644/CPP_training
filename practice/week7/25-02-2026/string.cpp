#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

TEST(StringMatchersTest, AllExamples)
{
    std::string text = "abc123xyz";
    
    EXPECT_THAT(text, StartsWith("abc"));
    EXPECT_THAT(text, EndsWith("xyz"));
    EXPECT_THAT(text, HasSubstr("123"));
    EXPECT_THAT(text, MatchesRegex("[a-z]+[0-9]+[a-z]+"));
    EXPECT_THAT(text, ContainsRegex("[0-9]+"));
}