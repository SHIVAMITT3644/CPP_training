#include "Road.h"

Road::Road(char roadId, ITrafficLight* trafficLight)
    : roadId_(roadId),
      trafficLight_(trafficLight)
{
}

char Road::getRoadId() const
{
    return roadId_;
}

ITrafficLight* Road::getTrafficLight() const
{
    return trafficLight_;
}