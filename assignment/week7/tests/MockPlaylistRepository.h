#ifndef MOCKPLAYLISTREPOSITORY_H
#define MOCKPLAYLISTREPOSITORY_H

#include <gmock/gmock.h>
#include "IPlaylistRepository.h"

class MockPlaylistRepository : public IPlaylistRepository
{
public:
    MOCK_METHOD(bool, save, (const IPlaylist& playlist), (override));
    MOCK_METHOD(bool, load, (const std::string& playlistName, IPlaylist& playlist), (override));
    MOCK_METHOD(std::vector<std::string>, listNames, (), (override));
    MOCK_METHOD(bool, remove, (const std::string& playlistName), (override));
};

#endif
