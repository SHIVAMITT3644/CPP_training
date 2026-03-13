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

char readRoadIdFromUser(const std::string& message)
{
    std::string input;

    while (true)
    {
        readCompleteLineInput(std::cin, input, message);

        if (input.length() == 1)
        {
            char roadId = std::toupper(static_cast<unsigned char>(input[0]));

            if (roadId == 'A' || roadId == 'B' || roadId == 'C' || roadId == 'D')
            {
                return roadId;
            }
        }

        std::cout << "Invalid road name. Please enter A, B, C or D.\n";
    }
}

void setupIntersection(IntersectionController& controller,
                        TrafficLight& lightA,
                        TrafficLight& lightB,
                        TrafficLight& lightC,
                        TrafficLight& lightD)
{
    Road roadA('A', &lightA);
    Road roadB('B', &lightB);
    Road roadC('C', &lightC);
    Road roadD('D', &lightD);

    controller.addRoad(roadA);
    controller.addRoad(roadB);
    controller.addRoad(roadC);
    controller.addRoad(roadD);
}

void runTrafficSimulation()
{
    IntersectionController controller;

    TrafficLight lightA;
    TrafficLight lightB;
    TrafficLight lightC;
    TrafficLight lightD;

    setupIntersection(controller, lightA, lightB, lightC, lightD);

    std::thread trafficThread(&IntersectionController::startTrafficCycle, &controller);

    bool shouldExit = false;

    while (!shouldExit)
    {
        tcflush(STDIN_FILENO, TCIFLUSH);

        std::cout << TRAFFIC_LIGHT_MENU;

        int choice = readValidUserInput(ENTER_YOUR_CHOICE_MESSAGE);

        if (choice == 1)
        {
            std::cout << ROAD_LAYOUT;

            char sourceRoad = readRoadIdFromUser("\nEnter source road name (A/B/C/D): ");
            char destinationRoad = readRoadIdFromUser("\nEnter destination road name (A/B/C/D): ");

            controller.processVehicle(sourceRoad, destinationRoad);

            tcflush(STDIN_FILENO, TCIFLUSH);
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

    controller.stopTrafficCycle();

    if (trafficThread.joinable())
    {
        trafficThread.join();
    }

    std::cout << EXIT_PROGRAM_MESSAGE;
}
