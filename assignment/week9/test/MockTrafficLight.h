#ifndef MOCKTRAFFICLIGHT_H
#define MOCKTRAFFICLIGHT_H

#include <gmock/gmock.h>
#include "ITrafficLight.h"

class MockTrafficLight : public ITrafficLight
{
public:
    MOCK_METHOD(void, makeGreen, (), (override));
    MOCK_METHOD(void, makeRed, (), (override));
    MOCK_METHOD(bool, isGreen, (), (const, override));
};

#endif
