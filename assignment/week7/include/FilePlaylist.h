#ifndef FILEPLAYLISTREPOSITORY_H
#define FILEPLAYLISTREPOSITORY_H

#include "IPlaylistRepository.h"

class FilePlaylistRepository : public IPlaylistRepository
{
public:
    bool save(const IPlaylist& playlist) override;
    bool load(const std::string& name, IPlaylist& playlist) override;
    std::vector<std::string> listNames() override;
    bool remove(const std::string& name) override;
};

#endif
