#ifndef ROAD_H
#define ROAD_H

#include "ITrafficLight.h"

class Road
{
    char roadId_;
    ITrafficLight* trafficLight_;

    public:
    Road(char roadId, ITrafficLight* trafficLight);

    char getRoadId() const;
    ITrafficLight* getTrafficLight() const;
};

#endif