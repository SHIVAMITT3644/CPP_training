#include "FilePlaylist.h"

#include <fstream>
#include <filesystem>
#include <iostream>

#include "Constants.h"

bool FilePlaylistRepository::save(const IPlaylist& playlist)
{
    bool isPlaylistSaved = false;
    std::ofstream playlistFile(PLAYLIST_FILE_PATH + playlist.getName() + TEXT_FILE_EXTENSION);

    if (playlistFile.is_open())
    {
        playlistFile << playlist.getName() << "\n";

        const std::vector<Song>& songs = playlist.getSongs();

        for (const Song& song : songs)
        {
            playlistFile << song.getId() << ","
                         << song.getTitle() << ","
                         << song.getArtist() << ","
                         << song.getDurationInSeconds() << ","
                         << song.getFilePath() << "\n";
        }

        isPlaylistSaved = true;
    }

    return isPlaylistSaved;
}

bool FilePlaylistRepository::load(const std::string& playlistName, IPlaylist& playlist)
{
    bool isPlaylistLoaded = false;
    std::ifstream playlistFile(PLAYLIST_FILE_PATH + playlistName + TEXT_FILE_EXTENSION);

    if (playlistFile.is_open())
    {
        std::string loadedPlaylistName;
        std::getline(playlistFile, loadedPlaylistName);

        playlist.setName(loadedPlaylistName);

        std::string songRecord;

        while (std::getline(playlistFile, songRecord))
        {
            size_t firstCommaPosition = songRecord.find(',');
            size_t secondCommaPosition = songRecord.find(',', firstCommaPosition + 1);
            size_t thirdCommaPosition = songRecord.find(',', secondCommaPosition + 1);
            size_t fourthCommaPosition = songRecord.find(',', thirdCommaPosition + 1);

            if (firstCommaPosition != std::string::npos &&
                secondCommaPosition != std::string::npos &&
                thirdCommaPosition != std::string::npos &&
                fourthCommaPosition != std::string::npos)
            {
                std::string songId = songRecord.substr(0, firstCommaPosition);
                std::string songTitle = songRecord.substr(firstCommaPosition + 1, secondCommaPosition - firstCommaPosition - 1);
                std::string songArtist = songRecord.substr(secondCommaPosition + 1, thirdCommaPosition - secondCommaPosition - 1);
                std::string songDurationText = songRecord.substr(thirdCommaPosition + 1, fourthCommaPosition - thirdCommaPosition - 1);
                std::string songFilePath = songRecord.substr(fourthCommaPosition + 1);

                int songDurationInSeconds = 0;
                bool isDurationValid = true;

                try
                {
                    songDurationInSeconds = std::stoi(songDurationText);
                }
                catch (const std::exception&)
                {
                    std::cerr << INVALID_TIME_DURATION_ERROR_MESSAGE;
                    isDurationValid = false;
                }

                if (isDurationValid)
                {
                    Song song(songId, songTitle, songArtist, songDurationInSeconds, songFilePath);
                    playlist.addSong(song);
                }
            }
        }

        isPlaylistLoaded = true;
    }

    return isPlaylistLoaded;
}

std::vector<std::string> FilePlaylistRepository::listNames()
{
    std::vector<std::string> playlistNames;

    if (std::filesystem::exists(PLAYLIST_FILE_PATH))
    {
        for (const auto& directoryEntry : std::filesystem::directory_iterator(PLAYLIST_FILE_PATH))
        {
            if (directoryEntry.path().extension() == TEXT_FILE_EXTENSION)
            {
                playlistNames.push_back(directoryEntry.path().stem().string());
            }
        }
    }

    return playlistNames;
}

bool FilePlaylistRepository::remove(const std::string& playlistName)
{
    bool isPlaylistRemoved = false;
    std::string playlistFilePath = std::string(PLAYLIST_FILE_PATH) + playlistName + TEXT_FILE_EXTENSION;

    if (std::filesystem::exists(playlistFilePath))
    {
        isPlaylistRemoved = std::filesystem::remove(playlistFilePath);
    }

    return isPlaylistRemoved;
}
