#include "TrafficLight.h"

TrafficLight::TrafficLight()
    : state_(State::Red)
{
}

void TrafficLight::makeGreen()
{
    state_ = State::Green;
}

void TrafficLight::makeRed()
{
    state_ = State::Red;
}

bool TrafficLight::isGreen() const
{
    return state_ == State::Green;
}

TrafficLight::State TrafficLight::getState() const
{
    return state_;
}
