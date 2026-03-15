#include <chrono>
#include <iostream>
#include <thread>

#include "Constants.h"
#include "IntersectionController.h"

IntersectionController::IntersectionController()
    : semaphore_(1),
      isRunning_(true),
      lastSwitchTime_(std::chrono::steady_clock::now())
{
}

bool IntersectionController::addRoad(const Road& road)
{
    bool isRoadAdded = false;

    auto result = roads_.insert({road.getroadName(), road});

    if (result.second)
    {
        isRoadAdded = true;
    }

    return isRoadAdded;
}

bool IntersectionController::switchLight(char roadName)
{
    bool isLightSwitched = false;

    semaphore_.acquire();

    auto roadIterator = roads_.find(roadName);

    if (roadIterator != roads_.end())
    {
        for (auto& [id, road] : roads_)
        {
            if (id == roadName)
            {
                road.getTrafficLight()->makeGreen();
            }
            else
            {
                road.getTrafficLight()->makeRed();
            }
        }

        lastSwitchTime_ = std::chrono::steady_clock::now();
        isLightSwitched = true;
    }

    semaphore_.release();

    return isLightSwitched;
}

bool IntersectionController::startTrafficCycle()
{
    bool isTrafficCycleStarted = false;

    if (!roads_.empty())
    {
        isTrafficCycleStarted = true;

        while (isRunning_)
        {
            for (auto& [id, road] : roads_)
            {
                if (!isRunning_)
                {
                    break;
                }

                switchLight(id);
                std::this_thread::sleep_for(std::chrono::seconds(GREEN_SIGNAL_DURATION_SECONDS));
            }
        }
    }

    return isTrafficCycleStarted;
}

bool IntersectionController::stopTrafficCycle()
{
    bool isTrafficCycleStopped = false;

    if (isRunning_)
    {
        isRunning_ = false;
        isTrafficCycleStopped = true;
    }

    return isTrafficCycleStopped;
}

bool IntersectionController::canPassLeft(char sourceRoad, char destinationRoad) const
{
    bool canPass = false;

    if (sourceRoad == FIRST_ROAD_NAME && destinationRoad == SECOND_ROAD_NAME)
    {
        canPass = true;
    }
    else if (sourceRoad == SECOND_ROAD_NAME && destinationRoad == THIRD_ROAD_NAME)
    {
        canPass = true;
    }
    else if (sourceRoad == THIRD_ROAD_NAME && destinationRoad == FOURTH_ROAD_NAME)
    {
        canPass = true;
    }
    else if (sourceRoad == FOURTH_ROAD_NAME && destinationRoad == FIRST_ROAD_NAME)
    {
        canPass = true;
    }

    return canPass;
}

bool IntersectionController::areValidRoads(char sourceRoad, char destinationRoad) const
{
    bool areValid = false;

    if (roads_.find(sourceRoad) != roads_.end() && roads_.find(destinationRoad) != roads_.end())
    {
        areValid = true;
    }

    return areValid;
}

bool IntersectionController::isLightGreen(char roadName)
{
    bool isGreen = false;

    semaphore_.acquire();

    auto roadIterator = roads_.find(roadName);

    if (roadIterator != roads_.end())
    {
        isGreen = roadIterator->second.getTrafficLight()->isGreen();
    }

    semaphore_.release();

    return isGreen;
}

char IntersectionController::getCurrentGreenRoad()
{
    char currentGreenRoad = '\0';

    semaphore_.acquire();

    for (auto& [id, road] : roads_)
    {
        if (road.getTrafficLight()->isGreen())
        {
            currentGreenRoad = id;
            break;
        }
    }

    semaphore_.release();

    return currentGreenRoad;
}

int IntersectionController::getRemainingTimeForGreen(char roadName)
{
    int remainingTime = 0;
    char currentGreenRoad = getCurrentGreenRoad();

    if (currentGreenRoad != '\0')
    {
        auto currentTime = std::chrono::steady_clock::now();
        int elapsedSeconds = static_cast<int>( std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastSwitchTime_).count());
        int remainingCurrentGreenTime = GREEN_SIGNAL_DURATION_SECONDS - elapsedSeconds;

        if (remainingCurrentGreenTime < 0)
        {
            remainingCurrentGreenTime = 0;
        }

        int currentIndex = currentGreenRoad - FIRST_ROAD_NAME;
        int targetIndex = roadName - FIRST_ROAD_NAME;
        int offset = targetIndex - currentIndex;

        if (offset < 0)
        {
            offset += 4;
        }

        if (offset == 0)
        {
            remainingTime = remainingCurrentGreenTime;
        }
        else
        {
            remainingTime =
                remainingCurrentGreenTime +
                ((offset - 1) * GREEN_SIGNAL_DURATION_SECONDS);
        }
    }

    return remainingTime;
}

bool IntersectionController::processVehicle(char sourceRoad, char destinationRoad)
{
    bool isVehicleProcessed = false;
    bool canProceed = true;

    if (!areValidRoads(sourceRoad, destinationRoad))
    {
        std::cout << INVALID_INPUT_ROAD_ERROR_MESSAGE;
        canProceed = false;
    }

    if (canProceed)
    {
        if (canPassLeft(sourceRoad, destinationRoad) && !isLightGreen(sourceRoad))
        {
            std::cout << ROAD << sourceRoad << PASS_BY_ROAD_MESSAGE << destinationRoad << ".\n";

            isVehicleProcessed = true;
        }
        else
        {
            int previousRemainingTime = -1;

            while (!isLightGreen(sourceRoad))
            {
                int remainingTime = getRemainingTimeForGreen(sourceRoad);

                if (remainingTime != previousRemainingTime)
                {
                    std::cout << "\n" << ROAD << sourceRoad << TIME_REMAINING_MESSAGE << remainingTime << SECOND << std::flush;
                    previousRemainingTime = remainingTime;
                }

                std::this_thread::sleep_for(std::chrono::seconds(1));
            }

            if (previousRemainingTime != -1)
            {
                std::cout << "\n";
            }

            std::cout << ROAD << sourceRoad << GREEN_LIGHT_MESSAGE << destinationRoad << ".\n";

            isVehicleProcessed = true;
        }
    }

    return isVehicleProcessed;
}
