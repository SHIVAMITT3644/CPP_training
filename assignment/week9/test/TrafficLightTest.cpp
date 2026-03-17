#include <gtest/gtest.h>
#include "TrafficLight.h"

TEST(TrafficLightTest, Constructor_WhenCreated_ThenInitialStateIsRed)
{
    TrafficLight light;

    EXPECT_FALSE(light.isGreen());
    EXPECT_EQ(light.getState(), TrafficLight::State::Red);
}

TEST(TrafficLightTest, MakeGreen_WhenCalled_ThenStateBecomesGreen)
{
    TrafficLight light;

    light.makeGreen();

    EXPECT_TRUE(light.isGreen());
    EXPECT_EQ(light.getState(), TrafficLight::State::Green);
}

TEST(TrafficLightTest, MakeRed_WhenCalledAfterGreen_ThenStateBecomesRed)
{
    TrafficLight light;
    light.makeGreen();

    light.makeRed();

    EXPECT_FALSE(light.isGreen());
    EXPECT_EQ(light.getState(), TrafficLight::State::Red);
}
