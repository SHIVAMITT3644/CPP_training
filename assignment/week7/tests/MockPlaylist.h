#ifndef MOCKPLAYLIST_H
#define MOCKPLAYLIST_H

#include <gmock/gmock.h>
#include "IPlaylist.h"

class MockPlaylist : public IPlaylist
{
public:
    MOCK_METHOD(std::string, getName, (), (const, override));
    MOCK_METHOD(void, setName, (const std::string& name), (override));
    MOCK_METHOD(void, clear, (), (override));

    MOCK_METHOD(bool, addSong, (const Song& song), (override));
    MOCK_METHOD(bool, removeSongById, (const std::string& songId), (override));

    MOCK_METHOD(bool, moveSongUp, (int index), (override));
    MOCK_METHOD(bool, moveSongDown, (int index), (override));

    MOCK_METHOD(bool, next, (), (override));
    MOCK_METHOD(bool, previous, (), (override));

    MOCK_METHOD(const Song*, getCurrentSong, (), (const, override));
    MOCK_METHOD(int, getCurrentSongIndex, (), (const, override));
    MOCK_METHOD(bool, setCurrentSongIndex, (int index), (override));

    MOCK_METHOD(int, getSongCount, (), (const, override));
    MOCK_METHOD(const std::vector<Song>&, getSongs, (), (const, override));

    MOCK_METHOD(bool, hasSongId, (const std::string& id), (const, override));
    MOCK_METHOD(bool, hasSongTitle, (const std::string& title), (const, override));
    MOCK_METHOD(bool, hasSongFilePath, (const std::string& filePath), (const, override));
};

#endif
