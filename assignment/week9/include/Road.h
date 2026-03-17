#ifndef ROAD_H
#define ROAD_H

#include "ITrafficLight.h"

class Road
{
    char roadName_;
    ITrafficLight* trafficLight_;

    public:
    Road(char roadName, ITrafficLight* trafficLight);

    char getroadName() const;
    ITrafficLight* getTrafficLight() const;
};

#endif
