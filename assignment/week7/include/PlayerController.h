#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <string>
#include "IAudioPlayer.h"
#include "IPlaylist.h"

class PlayerController
{
public:
    enum State
    {
        STOPPED,
        PLAYING,
        PAUSED
    };

private:
    IAudioPlayer& audioPlayer_;
    IPlaylist* activePlaylist_;
    std::string loadedSongId_;
    State state_;

public:
    PlayerController(IAudioPlayer& audioPlayer);

    void setActivePlaylist(IPlaylist* playlist);

    bool play();
    bool pause();
    bool stop();

    bool next();
    bool previous();

    State getState() const;
    IPlaylist* getActivePlaylist() const;
};

#endif
