#ifndef IPLAYLISTREPOSITORY_H
#define IPLAYLISTREPOSITORY_H

#include <string>
#include <vector>
#include "IPlaylist.h"

class IPlaylistRepository
{
public:
    virtual ~IPlaylistRepository() = default;

    virtual bool save(const IPlaylist& playlist) = 0;
    virtual bool load(const std::string& name, IPlaylist& playlist) = 0;
    virtual std::vector<std::string> listNames() = 0;
    virtual bool remove(const std::string& name) = 0;
};

#endif
