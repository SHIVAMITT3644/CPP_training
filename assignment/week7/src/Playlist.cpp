#include "Playlist.h"
#include <utility>

Playlist::Playlist() : currentIndex_(-1)
{
}

Playlist::Playlist(const std::string& name) : name_(name), currentIndex_(-1)
{
}

std::string Playlist::getName() const
{
    return name_;
}

void Playlist::setName(const std::string& name)
{
    name_ = name;
}

void Playlist::clear()
{
    name_.clear();
    songs_.clear();
    currentIndex_ = -1;
}

bool Playlist::addSong(const Song& song)
{
    bool isSongAdded = true;

    songs_.push_back(song);

    if (currentIndex_ == -1)
    {
        currentIndex_ = 0;
    }

    return isSongAdded;
}

bool Playlist::removeSongById(const std::string& songId)
{
    bool isSongRemoved = false;

    for (int songIndex = 0; songIndex < static_cast<int>(songs_.size()); songIndex++)
    {
        if (songs_[songIndex].getId() == songId)
        {
            songs_.erase(songs_.begin() + songIndex);
            isSongRemoved = true;

            if (songs_.empty())
            {
                currentIndex_ = -1;
            }
            else if (currentIndex_ == songIndex)
            {
                if (currentIndex_ >= static_cast<int>(songs_.size()))
                {
                    currentIndex_ = static_cast<int>(songs_.size()) - 1;
                }
            }
            else if (currentIndex_ > songIndex)
            {
                currentIndex_--;
            }

            break;
        }
    }

    return isSongRemoved;
}

bool Playlist::moveSongUp(int index)
{
    bool isSongMovedUp = false;

    if (index > 0 && index < static_cast<int>(songs_.size()))
    {
        std::swap(songs_[index], songs_[index - 1]);

        if (currentIndex_ == index)
        {
            currentIndex_--;
        }
        else if (currentIndex_ == index - 1)
        {
            currentIndex_++;
        }

        isSongMovedUp = true;
    }

    return isSongMovedUp;
}

bool Playlist::moveSongDown(int index)
{
    bool isSongMovedDown = false;

    if (index >= 0 && index < static_cast<int>(songs_.size()) - 1)
    {
        std::swap(songs_[index], songs_[index + 1]);

        if (currentIndex_ == index)
        {
            currentIndex_++;
        }
        else if (currentIndex_ == index + 1)
        {
            currentIndex_--;
        }

        isSongMovedDown = true;
    }

    return isSongMovedDown;
}

bool Playlist::next()
{
    bool hasMovedToNextSong = false;

    if (!songs_.empty() && currentIndex_ < static_cast<int>(songs_.size()) - 1)
    {
        currentIndex_++;
        hasMovedToNextSong = true;
    }

    return hasMovedToNextSong;
}

bool Playlist::previous()
{
    bool hasMovedToPreviousSong = false;

    if (!songs_.empty() && currentIndex_ > 0)
    {
        currentIndex_--;
        hasMovedToPreviousSong = true;
    }

    return hasMovedToPreviousSong;
}

const Song* Playlist::getCurrentSong() const
{
    const Song* currentSong = nullptr;

    if (currentIndex_ >= 0 && currentIndex_ < static_cast<int>(songs_.size()))
    {
        currentSong = &songs_[currentIndex_];
    }

    return currentSong;
}

int Playlist::getCurrentSongIndex() const
{
    return currentIndex_;
}

bool Playlist::setCurrentSongIndex(int index)
{
    bool isCurrentSongIndexSet = false;

    if (index >= 0 && index < static_cast<int>(songs_.size()))
    {
        currentIndex_ = index;
        isCurrentSongIndexSet = true;
    }

    return isCurrentSongIndexSet;
}

int Playlist::getSongCount() const
{
    return static_cast<int>(songs_.size());
}

const std::vector<Song>& Playlist::getSongs() const
{
    return songs_;
}

bool Playlist::hasSongId(const std::string& id) const
{
    bool isSongIdFound = false;

    for (const Song& song : songs_)
    {
        if (song.getId() == id)
        {
            isSongIdFound = true;
            break;
        }
    }

    return isSongIdFound;
}

bool Playlist::hasSongTitle(const std::string& title) const
{
    bool isSongTitleFound = false;

    for (const Song& song : songs_)
    {
        if (song.getTitle() == title)
        {
            isSongTitleFound = true;
            break;
        }
    }

    return isSongTitleFound;
}

bool Playlist::hasSongFilePath(const std::string& filePath) const
{
    bool isSongFilePathFound = false;

    for (const Song& song : songs_)
    {
        if (song.getFilePath() == filePath)
        {
            isSongFilePathFound = true;
            break;
        }
    }

    return isSongFilePathFound;
}
