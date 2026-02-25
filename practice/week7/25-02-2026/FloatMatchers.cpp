#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cmath>

using namespace testing;

TEST(FloatingPointMatchers, AllFloatingExamples)
{
    float f1 = 0.1f * 3;  
    float f2 = 0.3f;

    double d1 = std::nan("");
    double d2 = std::nan("");

    EXPECT_NE(f1, f2);  

    EXPECT_FLOAT_EQ(f1, f2);


    EXPECT_DOUBLE_EQ(0.1 * 3, 0.3);


    EXPECT_THAT(f1, FloatEq(f2));

    EXPECT_THAT(0.1 * 3, DoubleEq(0.3));


    float nf1 = std::nanf("");
    float nf2 = std::nanf("");
    EXPECT_THAT(nf1, NanSensitiveFloatEq(nf2));

    EXPECT_THAT(d1, NanSensitiveDoubleEq(d2));

    EXPECT_THAT(d1, IsNan());
}