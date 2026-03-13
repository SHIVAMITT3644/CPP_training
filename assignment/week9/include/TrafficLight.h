#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "ITrafficLight.h"

class TrafficLight : public ITrafficLight
{
public:
    enum class State
    {
        Red,
        Green
    };

    TrafficLight();

    void makeGreen() override;
    void makeRed() override;
    bool isGreen() const override;

    State getState() const;

private:
    State state_;
};

#endif