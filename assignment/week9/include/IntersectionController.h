#ifndef INTERSECTIONCONTROLLER_H
#define INTERSECTIONCONTROLLER_H

#include <atomic>
#include <map>
#include <semaphore>
#include "Road.h"

class IntersectionController
{
public:
    IntersectionController();

    void addRoad(const Road& road);

    void startTrafficCycle();
    void stopTrafficCycle();

    void switchLight(char roadId);
    void processVehicle(char sourceRoad, char destinationRoad);

    bool isLightGreen(char roadId) const;

private:
    bool canPassLeft(char sourceRoad, char destinationRoad) const;
    bool isLightGreen(char roadId);
    bool areValidRoads(char sourceRoad, char destinationRoad) const;


private:
    std::map<char, Road> roads_;
    std::binary_semaphore semaphore_;
    std::atomic<bool> isRunning_;
};

#endif
