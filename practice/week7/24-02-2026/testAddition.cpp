#include <gtest/gtest.h>
#include "addition.h"

TEST(AdditionTest, PositiveNumbers) {
    EXPECT_EQ(add(2, 3), 5);
}

TEST(AdditionTest, NegativeNumbers) {
    EXPECT_EQ(add(-2, -3), -5);
}

TEST(AdditionTest, MixedNumbers) {
    EXPECT_EQ(add(-2, 3), 1);
}