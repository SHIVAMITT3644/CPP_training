#ifndef INTERSECTIONCONTROLLER_H
#define INTERSECTIONCONTROLLER_H

#include <chrono>
#include <map>
#include <semaphore>

#include "Road.h"

class IntersectionController
{
private:
    std::map<char, Road> roads_;
    std::binary_semaphore semaphore_;
    bool isRunning_;
    std::chrono::steady_clock::time_point lastSwitchTime_;

    bool canPassLeft(char sourceRoad, char destinationRoad) const;
    bool areValidRoads(char sourceRoad, char destinationRoad) const;
    bool isLightGreen(char roadName);
    char getCurrentGreenRoad();
    int getRemainingTimeForGreen(char roadName);

public:
    IntersectionController();

    bool addRoad(const Road& road);
    bool startTrafficCycle();
    bool stopTrafficCycle();
    bool switchLight(char roadName);
    bool processVehicle(char sourceRoad, char destinationRoad);
};

#endif
