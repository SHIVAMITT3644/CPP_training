#include <iostream>
#include <string>
#include <thread>
#include <cctype>
#include <termios.h>
#include <unistd.h>

#include "Input.h"
#include "Constants.h"
#include "IntersectionController.h"
#include "TrafficSimulation.h"
#include "Road.h"
#include "TrafficLight.h"

char readroadNameFromUser(const std::string& message)
{
    std::string input;
    char roadName = '\0';
    bool isValidroadName = false;

    while (!isValidroadName)
    {
        readCompleteLineInput(std::cin, input, message);

        if (input.length() == 1)
        {
            roadName = std::toupper(static_cast<unsigned char>(input[0]));

            if (roadName == FIRST_ROAD_NAME ||
                roadName == SECOND_ROAD_NAME ||
                roadName == THIRD_ROAD_NAME ||
                roadName == FOURTH_ROAD_NAME)
            {
                isValidroadName = true;
            }
            else
            {
                std::cout << INVALID_ROAD_NAME_ERROR_MESSAGE;
            }
        }
        else
        {
            std::cout << INVALID_ROAD_NAME_ERROR_MESSAGE;
        }
    }

    return roadName;
}

void setupIntersection(IntersectionController& controller, TrafficLight& lightA, TrafficLight& lightB, TrafficLight& lightC,TrafficLight& lightD)
{
    Road roadA(FIRST_ROAD_NAME, &lightA);
    Road roadB(SECOND_ROAD_NAME, &lightB);
    Road roadC(THIRD_ROAD_NAME, &lightC);
    Road roadD(FOURTH_ROAD_NAME, &lightD);

    controller.addRoad(roadA);
    controller.addRoad(roadB);
    controller.addRoad(roadC);
    controller.addRoad(roadD);
}

std::thread startTrafficControllerThread(IntersectionController& controller)
{
    std::thread trafficThread(&IntersectionController::startTrafficCycle, &controller);
    return trafficThread;
}

void handleProcessVehicleOption(IntersectionController& controller)
{
    std::cout << ROAD_LAYOUT;

    char sourceRoad = readroadNameFromUser(SOURCE_ROAD_NAME_INPUT_MESSAGE);
    char destinationRoad = readroadNameFromUser(DESTINATION_ROAD_NAME_INPUT_MESSAGE);

    controller.processVehicle(sourceRoad, destinationRoad);

    tcflush(STDIN_FILENO, TCIFLUSH);
}

void handleMenuChoice(int choice, bool& shouldExit, IntersectionController& controller)
{
    if (choice == 1)
    {
        handleProcessVehicleOption(controller);
    }
    else if (choice == 2)
    {
        shouldExit = true;
    }
    else
    {
        std::cout << MAIN_LOOP_INVALID_INPUT_ERROR_MESSAGE;
    }
}

void stopTrafficControllerThread(IntersectionController& controller, std::thread& trafficThread)
{
    controller.stopTrafficCycle();

    if (trafficThread.joinable())
    {
        trafficThread.join();
    }
}

void runTrafficSimulation()
{
    IntersectionController controller;

    TrafficLight lightA;
    TrafficLight lightB;
    TrafficLight lightC;
    TrafficLight lightD;

    setupIntersection(controller, lightA, lightB, lightC, lightD);

    std::thread trafficThread = startTrafficControllerThread(controller);

    bool shouldExit = false;

    while (!shouldExit)
    {
        tcflush(STDIN_FILENO, TCIFLUSH);

        std::cout << TRAFFIC_LIGHT_MENU;

        int choice = readValidUserInput(ENTER_YOUR_CHOICE_MESSAGE);

        handleMenuChoice(choice, shouldExit, controller);
    }

    stopTrafficControllerThread(controller, trafficThread);

    std::cout << EXIT_PROGRAM_MESSAGE;
}
