#ifndef IPLAYLIST_H
#define IPLAYLIST_H

#include <string>
#include <vector>
#include "Song.h"

class IPlaylist
{
public:
    virtual ~IPlaylist() = default;

    virtual std::string getName() const = 0;
    virtual void setName(const std::string& name) = 0;
    virtual void clear() = 0;

    virtual bool addSong(const Song& song) = 0;
    virtual bool removeSongById(const std::string& songId) = 0;

    virtual bool moveSongUp(int index) = 0;
    virtual bool moveSongDown(int index) = 0;

    virtual bool next() = 0;
    virtual bool previous() = 0;

    virtual const Song* getCurrentSong() const = 0;
    virtual int getCurrentSongIndex() const = 0;
    virtual bool setCurrentSongIndex(int index) = 0;

    virtual int getSongCount() const = 0;
    virtual const std::vector<Song>& getSongs() const = 0;

    virtual bool hasSongId(const std::string& id) const = 0;
    virtual bool hasSongTitle(const std::string& title) const = 0;
    virtual bool hasSongFilePath(const std::string& filePath) const = 0;
};

#endif
