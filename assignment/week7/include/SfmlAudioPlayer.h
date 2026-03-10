#ifndef SFMLAUDIOPLAYER_H
#define SFMLAUDIOPLAYER_H

#include <SFML/Audio.hpp>
#include <string>
#include "IAudioPlayer.h"

class SfmlAudioPlayer : public IAudioPlayer
{
private:
    sf::Music music_;

public:
    bool load(const std::string& filePath) override;
    void play() override;
    void pause() override;
    void stop() override;
};

#endif
