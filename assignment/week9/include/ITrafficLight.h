#ifndef ITRAFFICLIGHT_H
#define ITRAFFICLIGHT_H

class ITrafficLight
{
public:
    virtual ~ITrafficLight() = default;

    virtual void makeGreen() = 0;
    virtual void makeRed() = 0;
    virtual bool isGreen() const = 0;
};

#endif