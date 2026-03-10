#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>
#include "Song.h"
#include "IPlaylist.h"

class Playlist : public IPlaylist
{
private:
    std::string name_;
    std::vector<Song> songs_;
    int currentIndex_;

public:
    Playlist();
    Playlist(const std::string& name);

    std::string getName() const override;
    void setName(const std::string& name) override;
    void clear() override;

    bool addSong(const Song& song) override;
    bool removeSongById(const std::string& songId) override;

    bool moveSongUp(int index) override;
    bool moveSongDown(int index) override;

    bool next() override;
    bool previous() override;

    const Song* getCurrentSong() const override;
    int getCurrentSongIndex() const override;
    bool setCurrentSongIndex(int index) override;

    int getSongCount() const override;
    const std::vector<Song>& getSongs() const override;

    bool hasSongId(const std::string& id) const override;
    bool hasSongTitle(const std::string& title) const override;
    bool hasSongFilePath(const std::string& filePath) const override;
};

#endif
