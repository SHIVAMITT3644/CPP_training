#include "Road.h"

Road::Road(char roadName, ITrafficLight* trafficLight)
    : roadName_(roadName),
      trafficLight_(trafficLight)
{
}

char Road::getroadName() const
{
    return roadName_;
}

ITrafficLight* Road::getTrafficLight() const
{
    return trafficLight_;
}
