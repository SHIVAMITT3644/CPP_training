#include "PlayerController.h"

PlayerController::PlayerController(IAudioPlayer& audioPlayer)
    : audioPlayer_(audioPlayer),
      activePlaylist_(nullptr),
      loadedSongId_(""),
      state_(STOPPED)
{
}

void PlayerController::setActivePlaylist(IPlaylist* playlist)
{
    if (activePlaylist_ != playlist)
    {
        if (state_ == PLAYING || state_ == PAUSED)
        {
            audioPlayer_.stop();
        }

        activePlaylist_ = playlist;
        loadedSongId_.clear();
        state_ = STOPPED;
    }
}

bool PlayerController::play()
{
    bool isPlayed = false;

    if (activePlaylist_ != nullptr)
    {
        const Song* currentSong = activePlaylist_->getCurrentSong();

        if (currentSong != nullptr)
        {
            if (state_ == PAUSED && loadedSongId_ == currentSong->getId())
            {
                audioPlayer_.play();
                state_ = PLAYING;
                isPlayed = true;
            }
            else if (loadedSongId_ != currentSong->getId())
            {
                if (audioPlayer_.load(currentSong->getFilePath()))
                {
                    loadedSongId_ = currentSong->getId();
                    audioPlayer_.play();
                    state_ = PLAYING;
                    isPlayed = true;
                }
            }
            else
            {
                audioPlayer_.play();
                state_ = PLAYING;
                isPlayed = true;
            }
        }
    }

    return isPlayed;
}

bool PlayerController::pause()
{
    bool isPaused = false;

    if (state_ == PLAYING)
    {
        audioPlayer_.pause();
        state_ = PAUSED;
        isPaused = true;
    }

    return isPaused;
}

bool PlayerController::stop()
{
    bool isStopped = false;

    if (state_ == PLAYING || state_ == PAUSED)
    {
        audioPlayer_.stop();
        state_ = STOPPED;
        isStopped = true;
    }

    return isStopped;
}

bool PlayerController::next()
{
    bool isMovedToNextSong = false;

    if (activePlaylist_ != nullptr)
    {
        if (activePlaylist_->next())
        {
            const Song* currentSong = activePlaylist_->getCurrentSong();

            if (currentSong != nullptr)
            {
                if (audioPlayer_.load(currentSong->getFilePath()))
                {
                    loadedSongId_ = currentSong->getId();

                    if (state_ == PLAYING)
                    {
                        audioPlayer_.play();
                    }
                    else if (state_ == PAUSED)
                    {
                        state_ = STOPPED;
                    }

                    isMovedToNextSong = true;
                }
            }
        }
    }

    return isMovedToNextSong;
}

bool PlayerController::previous()
{
    bool isMovedToPreviousSong = false;

    if (activePlaylist_ != nullptr)
    {
        if (activePlaylist_->previous())
        {
            const Song* currentSong = activePlaylist_->getCurrentSong();

            if (currentSong != nullptr)
            {
                if (audioPlayer_.load(currentSong->getFilePath()))
                {
                    loadedSongId_ = currentSong->getId();

                    if (state_ == PLAYING)
                    {
                        audioPlayer_.play();
                    }
                    else if (state_ == PAUSED)
                    {
                        state_ = STOPPED;
                    }

                    isMovedToPreviousSong = true;
                }
            }
        }
    }

    return isMovedToPreviousSong;
}

PlayerController::State PlayerController::getState() const
{
    return state_;
}

IPlaylist* PlayerController::getActivePlaylist() const
{
    return activePlaylist_;
}
