#include <chrono>
#include <iostream>
#include <thread>

#include "Constants.h"
#include "IntersectionController.h"

IntersectionController::IntersectionController()
    : semaphore_(1),
      isRunning_(true)
{
}

void IntersectionController::addRoad(const Road& road)
{
    roads_.insert({road.getRoadId(), road});
}

void IntersectionController::switchLight(char roadId)
{
    semaphore_.acquire();

    for (auto& [id, road] : roads_)
    {
        if (id == roadId)
        {
            road.getTrafficLight()->makeGreen();
        }
        else
        {
            road.getTrafficLight()->makeRed();
        }
    }

    semaphore_.release();
}

void IntersectionController::startTrafficCycle()
{
    while (isRunning_)
    {
        for (auto& [id, road] : roads_)
        {
            if (!isRunning_)
            {
                break;
            }

            switchLight(id);
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }
    }
}

void IntersectionController::stopTrafficCycle()
{
    isRunning_ = false;
}

bool IntersectionController::canPassLeft(char sourceRoad, char destinationRoad) const
{
    if (sourceRoad == 'A' && destinationRoad == 'B')
    {
        return true;
    }

    if (sourceRoad == 'B' && destinationRoad == 'C')
    {
        return true;
    }

    if (sourceRoad == 'C' && destinationRoad == 'D')
    {
        return true;
    }

    if (sourceRoad == 'D' && destinationRoad == 'A')
    {
        return true;
    }

    return false;
}

bool IntersectionController::areValidRoads(char sourceRoad, char destinationRoad) const
{
    return roads_.find(sourceRoad) != roads_.end() &&
           roads_.find(destinationRoad) != roads_.end();
}

bool IntersectionController::isLightGreen(char roadId)
{
    bool isGreen = false;

    semaphore_.acquire();

    auto roadIterator = roads_.find(roadId);

    if (roadIterator != roads_.end())
    {
        isGreen = roadIterator->second.getTrafficLight()->isGreen();
    }

    semaphore_.release();

    return isGreen;
}

void IntersectionController::processVehicle(char sourceRoad, char destinationRoad)
{
    if (!areValidRoads(sourceRoad, destinationRoad))
    {
        std::cout << INVALID_INPUT_ROAD_ERROR_MESSAGE;
        return;
    }

    if (sourceRoad == destinationRoad)
    {
        std::cout << SAME_ROAD_ERROR_MESSAGE << sourceRoad << ".\n";
        return;
    }

    if (canPassLeft(sourceRoad, destinationRoad) && !isLightGreen(sourceRoad))
    {
        std::cout << ROAD << sourceRoad
              << PASS_BY_ROAD_MESSAGE
              << destinationRoad << ".\n";
              
        return;
    }

    bool isWaitingMessageShown = false;

    while (!isLightGreen(sourceRoad))
    {
        if (!isWaitingMessageShown)
        {
            std::cout << ROAD << sourceRoad << RED_LIGHT_MESSAGE;

            isWaitingMessageShown = true;
        }

        // std::cout << "waiting";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << ROAD << sourceRoad
              << GREEN_LIGHT_MESSAGE
              << destinationRoad << ".\n";
}
