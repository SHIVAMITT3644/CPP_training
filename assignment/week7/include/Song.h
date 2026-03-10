#ifndef SONG_H
#define SONG_H

#include <string>

class Song
{
private:
    std::string id_;
    std::string title_;
    std::string artist_;
    int durationInSeconds_;
    std::string filePath_;

public:
    Song();
    Song(const std::string& id,
         const std::string& title,
         const std::string& artist,
         int durationInSeconds,
         const std::string& filePath);

    std::string getId() const;
    std::string getTitle() const;
    std::string getArtist() const;
    int getDurationInSeconds() const;
    std::string getFilePath() const;
};

#endif
