#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "IntersectionController.h"
#include "Road.h"
#include "MockTrafficLight.h"

using ::testing::Return;

class IntersectionControllerTest : public ::testing::Test
{
protected:
    IntersectionController controller;
    MockTrafficLight lightA;
    MockTrafficLight lightB;
    MockTrafficLight lightC;
    MockTrafficLight lightD;
};

TEST_F(IntersectionControllerTest, AddRoad_WhenRoadIsAddedFirstTime_ThenReturnsTrue)
{
    EXPECT_TRUE(controller.addRoad(Road('A', &lightA)));
}

TEST_F(IntersectionControllerTest, AddRoad_WhenDuplicateRoadIsAdded_ThenReturnsFalse)
{
    EXPECT_TRUE(controller.addRoad(Road('A', &lightA)));
    EXPECT_FALSE(controller.addRoad(Road('A', &lightA)));
}

    TEST_F(IntersectionControllerTest, SwitchLight_WhenValidroadNameIsPassed_ThenReturnsTrue)
    {
        controller.addRoad(Road('A', &lightA));
        controller.addRoad(Road('B', &lightB));
        controller.addRoad(Road('C', &lightC));
        controller.addRoad(Road('D', &lightD));

        EXPECT_CALL(lightA, makeGreen()).Times(1);
        EXPECT_CALL(lightB, makeRed()).Times(1);
        EXPECT_CALL(lightC, makeRed()).Times(1);
        EXPECT_CALL(lightD, makeRed()).Times(1);

        EXPECT_TRUE(controller.switchLight('A'));
    }

TEST_F(IntersectionControllerTest, SwitchLight_WhenInvalidroadNameIsPassed_ThenReturnsFalse)
{
    controller.addRoad(Road('A', &lightA));
    controller.addRoad(Road('B', &lightB));
    controller.addRoad(Road('C', &lightC));
    controller.addRoad(Road('D', &lightD));

    EXPECT_FALSE(controller.switchLight('X'));
}

TEST_F(IntersectionControllerTest, StopTrafficCycle_WhenControllerIsRunning_ThenReturnsTrue)
{
    EXPECT_TRUE(controller.stopTrafficCycle());
}

TEST_F(IntersectionControllerTest, StopTrafficCycle_WhenControllerAlreadyStopped_ThenReturnsFalse)
{
    EXPECT_TRUE(controller.stopTrafficCycle());
    EXPECT_FALSE(controller.stopTrafficCycle());
}

TEST_F(IntersectionControllerTest, StartTrafficCycle_WhenNoRoadsAreAdded_ThenReturnsFalse)
{
    EXPECT_FALSE(controller.startTrafficCycle());
}

TEST_F(IntersectionControllerTest, StartTrafficCycle_WhenRoadsExistAndControllerAlreadyStopped_ThenReturnsTrue)
{
    controller.addRoad(Road('A', &lightA));
    controller.addRoad(Road('B', &lightB));
    controller.addRoad(Road('C', &lightC));
    controller.addRoad(Road('D', &lightD));

    EXPECT_TRUE(controller.stopTrafficCycle());
    EXPECT_TRUE(controller.startTrafficCycle());
}

TEST_F(IntersectionControllerTest, ProcessVehicle_WhenRoadIsInvalid_ThenReturnsFalse)
{
    controller.addRoad(Road('A', &lightA));
    controller.addRoad(Road('B', &lightB));
    controller.addRoad(Road('C', &lightC));
    controller.addRoad(Road('D', &lightD));

    EXPECT_FALSE(controller.processVehicle('X', 'B'));
}

TEST_F(IntersectionControllerTest, ProcessVehicle_WhenLeftPassAllowedAndLightIsRed_ThenReturnsTrue)
{
    controller.addRoad(Road('A', &lightA));
    controller.addRoad(Road('B', &lightB));
    controller.addRoad(Road('C', &lightC));
    controller.addRoad(Road('D', &lightD));

    EXPECT_CALL(lightA, isGreen()).WillOnce(Return(false));

    EXPECT_TRUE(controller.processVehicle('A', 'B'));
}

TEST_F(IntersectionControllerTest, ProcessVehicle_WhenSourceRoadIsAlreadyGreen_ThenReturnsTrue)
{
    controller.addRoad(Road('A', &lightA));
    controller.addRoad(Road('B', &lightB));
    controller.addRoad(Road('C', &lightC));
    controller.addRoad(Road('D', &lightD));

    EXPECT_CALL(lightA, isGreen()).WillOnce(Return(true));

    EXPECT_TRUE(controller.processVehicle('A', 'C'));
}
