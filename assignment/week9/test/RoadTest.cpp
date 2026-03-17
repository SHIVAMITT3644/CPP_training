#include <gtest/gtest.h>
#include "Road.h"
#include "TrafficLight.h"

TEST(RoadTest, Constructor_WhenRoadCreated_ThenStoresroadNameAndTrafficLightPointer)
{
    TrafficLight light;
    Road road('A', &light);

    EXPECT_EQ(road.getroadName(), 'A');
    EXPECT_EQ(road.getTrafficLight(), &light);
}
