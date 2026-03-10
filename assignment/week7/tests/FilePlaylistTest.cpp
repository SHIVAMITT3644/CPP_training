#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "FilePlaylist.h"
#include "Playlist.h"
#include "Constants.h"

class FilePlaylistRepositoryTest : public ::testing::Test
{
protected:
    FilePlaylistRepository repository_;
    std::string playlistName_{"TestPlaylist"};

    std::string playlistFilePath_ =
        std::string(PLAYLIST_FILE_PATH) + playlistName_ + TEXT_FILE_EXTENSION;

    Song song1_{"1", "Believer", "Imagine Dragons", 204, "resources/audio/song1.wav"};
    Song song2_{"2", "Numb", "Linkin Park", 185, "resources/audio/song2.wav"};

    void SetUp() override
    {
        std::filesystem::create_directories(PLAYLIST_FILE_PATH);

        if (std::filesystem::exists(playlistFilePath_))
        {
            std::filesystem::remove(playlistFilePath_);
        }
    }

    void TearDown() override
    {
        if (std::filesystem::exists(playlistFilePath_))
        {
            std::filesystem::remove(playlistFilePath_);
        }
    }
};

TEST_F(FilePlaylistRepositoryTest, Save_WhenPlaylistIsValid_ThenCreatesPlaylistFileAndReturnsTrue)
{
    Playlist playlist(playlistName_);
    playlist.addSong(song1_);
    playlist.addSong(song2_);

    bool result = repository_.save(playlist);

    EXPECT_TRUE(result);
    EXPECT_TRUE(std::filesystem::exists(playlistFilePath_));
}

TEST_F(FilePlaylistRepositoryTest, Load_WhenPlaylistFileExists_ThenLoadsPlaylistDataAndReturnsTrue)
{
    Playlist playlistToSave(playlistName_);
    playlistToSave.addSong(song1_);
    playlistToSave.addSong(song2_);
    ASSERT_TRUE(repository_.save(playlistToSave));

    Playlist loadedPlaylist;

    bool result = repository_.load(playlistName_, loadedPlaylist);

    EXPECT_TRUE(result);
    EXPECT_EQ(loadedPlaylist.getName(), playlistName_);
    EXPECT_EQ(loadedPlaylist.getSongCount(), 2);

    const std::vector<Song>& loadedSongs = loadedPlaylist.getSongs();
    ASSERT_EQ(loadedSongs.size(), 2);

    EXPECT_EQ(loadedSongs[0].getId(), "1");
    EXPECT_EQ(loadedSongs[0].getTitle(), "Believer");
    EXPECT_EQ(loadedSongs[0].getArtist(), "Imagine Dragons");
    EXPECT_EQ(loadedSongs[0].getDurationInSeconds(), 204);
    EXPECT_EQ(loadedSongs[0].getFilePath(), "resources/audio/song1.wav");

    EXPECT_EQ(loadedSongs[1].getId(), "2");
    EXPECT_EQ(loadedSongs[1].getTitle(), "Numb");
    EXPECT_EQ(loadedSongs[1].getArtist(), "Linkin Park");
    EXPECT_EQ(loadedSongs[1].getDurationInSeconds(), 185);
    EXPECT_EQ(loadedSongs[1].getFilePath(), "resources/audio/song2.wav");
}

TEST_F(FilePlaylistRepositoryTest, Load_WhenPlaylistFileDoesNotExist_ThenReturnsFalse)
{
    Playlist loadedPlaylist;

    bool result = repository_.load("UnknownPlaylist", loadedPlaylist);

    EXPECT_FALSE(result);
}

TEST_F(FilePlaylistRepositoryTest, ListNames_WhenPlaylistFilesExist_ThenReturnsPlaylistNames)
{
    Playlist playlist1("PlaylistOne");
    Playlist playlist2("PlaylistTwo");

    playlist1.addSong(song1_);
    playlist2.addSong(song2_);

    ASSERT_TRUE(repository_.save(playlist1));
    ASSERT_TRUE(repository_.save(playlist2));

    std::vector<std::string> playlistNames = repository_.listNames();

    EXPECT_NE(std::find(playlistNames.begin(), playlistNames.end(), "PlaylistOne"), playlistNames.end());
    EXPECT_NE(std::find(playlistNames.begin(), playlistNames.end(), "PlaylistTwo"), playlistNames.end());

    std::filesystem::remove(std::string(PLAYLIST_FILE_PATH) + "PlaylistOne" + TEXT_FILE_EXTENSION);
    std::filesystem::remove(std::string(PLAYLIST_FILE_PATH) + "PlaylistTwo" + TEXT_FILE_EXTENSION);
}

TEST_F(FilePlaylistRepositoryTest, Remove_WhenPlaylistFileExists_ThenDeletesFileAndReturnsTrue)
{
    Playlist playlist(playlistName_);
    playlist.addSong(song1_);
    ASSERT_TRUE(repository_.save(playlist));
    ASSERT_TRUE(std::filesystem::exists(playlistFilePath_));

    bool result = repository_.remove(playlistName_);

    EXPECT_TRUE(result);
    EXPECT_FALSE(std::filesystem::exists(playlistFilePath_));
}

TEST_F(FilePlaylistRepositoryTest, Remove_WhenPlaylistFileDoesNotExist_ThenReturnsFalse)
{
    bool result = repository_.remove("UnknownPlaylist");

    EXPECT_FALSE(result);
}
