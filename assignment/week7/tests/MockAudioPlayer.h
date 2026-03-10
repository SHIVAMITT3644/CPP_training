#ifndef MOCKAUDIOPLAYER_H
#define MOCKAUDIOPLAYER_H

#include <gmock/gmock.h>
#include "IAudioPlayer.h"

class MockAudioPlayer : public IAudioPlayer
{
public:
    MOCK_METHOD(bool, load, (const std::string& filePath), (override));
    MOCK_METHOD(void, play, (), (override));
    MOCK_METHOD(void, pause, (), (override));
    MOCK_METHOD(void, stop, (), (override));
};

#endif
