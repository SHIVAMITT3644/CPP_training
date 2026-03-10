#include "SfmlAudioPlayer.h"

bool SfmlAudioPlayer::load(const std::string& filePath)
{
    return music_.openFromFile(filePath);
}

void SfmlAudioPlayer::play()
{
    music_.play();
}

void SfmlAudioPlayer::pause()
{
    music_.pause();
}

void SfmlAudioPlayer::stop()
{
    music_.stop();
}
