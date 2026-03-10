#ifndef IAUDIOPLAYER_H
#define IAUDIOPLAYER_H

#include <string>

class IAudioPlayer
{
public:
    virtual ~IAudioPlayer() = default;

    virtual bool load(const std::string& filePath) = 0;
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
};

#endif