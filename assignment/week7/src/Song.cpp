#include "Song.h"

Song::Song() : durationInSeconds_(0)
{
}

Song::Song(const std::string& id,
           const std::string& title,
           const std::string& artist,
           int durationInSeconds,
           const std::string& filePath)
    : id_(id),
      title_(title),
      artist_(artist),
      durationInSeconds_(durationInSeconds),
      filePath_(filePath)
{
}

std::string Song::getId() const
{
    return id_;
}

std::string Song::getTitle() const
{
    return title_;
}

std::string Song::getArtist() const
{
    return artist_;
}

int Song::getDurationInSeconds() const
{
    return durationInSeconds_;
}

std::string Song::getFilePath() const
{
    return filePath_;
}
