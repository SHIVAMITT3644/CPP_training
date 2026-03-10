#ifndef PLAYLISTLIBRARY_H
#define PLAYLISTLIBRARY_H

#include <string>
#include <unordered_map>
#include <vector>

#include "IPlaylistRepository.h"
#include "IPlaylist.h"
#include "Playlist.h"
#include "Song.h"

class PlaylistLibrary
{
private:
    IPlaylistRepository& repository_;
    std::unordered_map<std::string, Playlist> playlists_;
    std::vector<Song> availableSongs_;
    bool parseSongRecord(const std::string& songRecord, Song& song) const;

public:
    PlaylistLibrary(IPlaylistRepository& repository);

    bool createPlaylist(const std::string& playlistName);
    bool deletePlaylist(const std::string& playlistName);

    IPlaylist* getPlaylist(const std::string& playlistName);
    std::vector<std::string> getPlaylistNames() const;
    std::vector<std::string> getAllPlaylistNames();

    bool savePlaylist(const std::string& playlistName);
    bool loadPlaylist(const std::string& playlistName);

    bool loadAvailableSongs(const std::string& fileName);
    const std::vector<Song>& getAvailableSongs() const;
    const Song* findAvailableSongById(const std::string& songId) const;
};

#endif
