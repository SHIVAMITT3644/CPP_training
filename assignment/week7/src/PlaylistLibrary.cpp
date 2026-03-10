#include "PlaylistLibrary.h"

#include <algorithm>
#include <fstream>
#include <iostream>

#include "Constants.h"

PlaylistLibrary::PlaylistLibrary(IPlaylistRepository& repository)
    : repository_(repository)
{
}

bool PlaylistLibrary::createPlaylist(const std::string& playlistName)
{
    bool isPlaylistCreated = false;

    if (!playlistName.empty() && playlists_.find(playlistName) == playlists_.end())
    {
        playlists_.insert({playlistName, Playlist(playlistName)});
        isPlaylistCreated = true;
    }

    return isPlaylistCreated;
}

bool PlaylistLibrary::deletePlaylist(const std::string& playlistName)
{
    bool isPlaylistDeleted = false;

    auto playlistIterator = playlists_.find(playlistName);

    if (playlistIterator != playlists_.end())
    {
        playlists_.erase(playlistIterator);
        repository_.remove(playlistName);
        isPlaylistDeleted = true;
    }
    else
    {
        if (repository_.remove(playlistName))
        {
            isPlaylistDeleted = true;
        }
    }

    return isPlaylistDeleted;
}

IPlaylist* PlaylistLibrary::getPlaylist(const std::string& playlistName)
{
    IPlaylist* playlist = nullptr;

    auto playlistIterator = playlists_.find(playlistName);

    if (playlistIterator != playlists_.end())
    {
        playlist = &(playlistIterator->second);
    }

    return playlist;
}

std::vector<std::string> PlaylistLibrary::getPlaylistNames() const
{
    std::vector<std::string> playlistNames;

    for (const auto& playlistEntry : playlists_)
    {
        playlistNames.push_back(playlistEntry.first);
    }

    return playlistNames;
}

std::vector<std::string> PlaylistLibrary::getAllPlaylistNames()
{
    std::vector<std::string> allPlaylistNames = getPlaylistNames();
    std::vector<std::string> savedPlaylistNames = repository_.listNames();

    for (const std::string& savedPlaylistName : savedPlaylistNames)
    {
        if (std::find(allPlaylistNames.begin(), allPlaylistNames.end(), savedPlaylistName) == allPlaylistNames.end())
        {
            allPlaylistNames.push_back(savedPlaylistName);
        }
    }

    return allPlaylistNames;
}

bool PlaylistLibrary::savePlaylist(const std::string& playlistName)
{
    bool isPlaylistSaved = false;

    auto playlistIterator = playlists_.find(playlistName);

    if (playlistIterator != playlists_.end())
    {
        isPlaylistSaved = repository_.save(playlistIterator->second);
    }

    return isPlaylistSaved;
}

bool PlaylistLibrary::loadPlaylist(const std::string& playlistName)
{
    bool isPlaylistLoaded = false;
    Playlist playlist;

    if (!playlistName.empty())
    {
        if (repository_.load(playlistName, playlist))
        {
            playlists_[playlist.getName()] = playlist;
            isPlaylistLoaded = true;
        }
    }

    return isPlaylistLoaded;
}

bool PlaylistLibrary::loadAvailableSongs(const std::string& fileName)
{
    bool areAvailableSongsLoaded = false;

    std::ifstream availableSongsFile(fileName);

    if (availableSongsFile.is_open())
    {
        availableSongs_.clear();
        std::string songRecord;

        while (std::getline(availableSongsFile, songRecord))
        {
            Song song;
            bool isSongParsed = parseSongRecord(songRecord, song);

            if (isSongParsed)
            {
                availableSongs_.push_back(song);
            }
        }

        areAvailableSongsLoaded = true;
    }

    return areAvailableSongsLoaded;
}

bool PlaylistLibrary::parseSongRecord(const std::string& songRecord, Song& song) const
{
    bool isSongParsed = false;

    size_t firstCommaPosition = songRecord.find(',');
    size_t secondCommaPosition = songRecord.find(',', firstCommaPosition + 1);
    size_t thirdCommaPosition = songRecord.find(',', secondCommaPosition + 1);
    size_t fourthCommaPosition = songRecord.find(',', thirdCommaPosition + 1);

    if (firstCommaPosition != std::string::npos && secondCommaPosition != std::string::npos &&
        thirdCommaPosition != std::string::npos && fourthCommaPosition != std::string::npos)
    {
        std::string songId = songRecord.substr(0, firstCommaPosition);
        std::string songTitle = songRecord.substr(firstCommaPosition + 1, secondCommaPosition - firstCommaPosition - 1);
        std::string songArtist = songRecord.substr(secondCommaPosition + 1, thirdCommaPosition - secondCommaPosition - 1);
        std::string songDurationText = songRecord.substr(thirdCommaPosition + 1, fourthCommaPosition - thirdCommaPosition - 1);
        std::string songFilePath = songRecord.substr(fourthCommaPosition + 1);

        bool isDurationValid = true;

        for (char character : songDurationText)
        {
            if (!std::isdigit(character))
            {
                isDurationValid = false;
                break;
            }
        }

        if (isDurationValid)
        {
            int songDurationInSeconds = std::stoi(songDurationText);

            if (songDurationInSeconds > 0)
            {
                song = Song(songId, songTitle, songArtist, songDurationInSeconds, songFilePath);
                isSongParsed = true;
            }
        }
    }

    return isSongParsed;
}

const std::vector<Song>& PlaylistLibrary::getAvailableSongs() const
{
    return availableSongs_;
}

const Song* PlaylistLibrary::findAvailableSongById(const std::string& songId) const
{
    const Song* foundSong = nullptr;

    for (const Song& song : availableSongs_)
    {
        if (song.getId() == songId)
        {
            foundSong = &song;
            break;
        }
    }

    return foundSong;
}
