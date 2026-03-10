#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <filesystem>
#include <fstream>
#include <vector>
#include <string>

#include "PlaylistLibrary.h"
#include "MockPlaylistRepository.h"

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

class PlaylistLibraryTest : public ::testing::Test
{
protected:
    MockPlaylistRepository mockRepository_;
    PlaylistLibrary library_{mockRepository_};

    std::filesystem::path tempSongsFilePath_ =
        std::filesystem::temp_directory_path() / "playlist_library_songs_test.txt";

    void TearDown() override
    {
        if (std::filesystem::exists(tempSongsFilePath_))
        {
            std::filesystem::remove(tempSongsFilePath_);
        }
    }
};

TEST_F(PlaylistLibraryTest, CreatePlaylist_WhenNameIsValidAndUnique_ThenCreatesPlaylist)
{
    bool result = library_.createPlaylist("Workout");

    EXPECT_TRUE(result);
    EXPECT_NE(library_.getPlaylist("Workout"), nullptr);
}

TEST_F(PlaylistLibraryTest, CreatePlaylist_WhenNameIsEmptyOrDuplicate_ThenReturnsFalse)
{
    EXPECT_FALSE(library_.createPlaylist(""));

    ASSERT_TRUE(library_.createPlaylist("Workout"));
    EXPECT_FALSE(library_.createPlaylist("Workout"));
}

TEST_F(PlaylistLibraryTest, DeletePlaylist_WhenPlaylistExistsInMemory_ThenDeletesPlaylistAndReturnsTrue)
{
    ASSERT_TRUE(library_.createPlaylist("Workout"));

    EXPECT_CALL(mockRepository_, remove("Workout"))
        .Times(1)
        .WillOnce(Return(true));

    bool result = library_.deletePlaylist("Workout");

    EXPECT_TRUE(result);
    EXPECT_EQ(library_.getPlaylist("Workout"), nullptr);
}

TEST_F(PlaylistLibraryTest, DeletePlaylist_WhenPlaylistDoesNotExistInMemoryButExistsInRepository_ThenReturnsTrue)
{
    EXPECT_CALL(mockRepository_, remove("SavedPlaylist"))
        .Times(1)
        .WillOnce(Return(true));

    bool result = library_.deletePlaylist("SavedPlaylist");

    EXPECT_TRUE(result);
}

TEST_F(PlaylistLibraryTest, GetPlaylist_WhenPlaylistDoesNotExist_ThenReturnsNullptr)
{
    EXPECT_EQ(library_.getPlaylist("Unknown"), nullptr);
}

TEST_F(PlaylistLibraryTest, GetPlaylistNames_WhenPlaylistsExistInMemory_ThenReturnsAllMemoryPlaylistNames)
{
    ASSERT_TRUE(library_.createPlaylist("Workout"));
    ASSERT_TRUE(library_.createPlaylist("Travel"));

    std::vector<std::string> playlistNames = library_.getPlaylistNames();

    EXPECT_EQ(playlistNames.size(), 2);
    EXPECT_NE(std::find(playlistNames.begin(), playlistNames.end(), "Workout"), playlistNames.end());
    EXPECT_NE(std::find(playlistNames.begin(), playlistNames.end(), "Travel"), playlistNames.end());
}

TEST_F(PlaylistLibraryTest, GetAllPlaylistNames_WhenRepositoryContainsAdditionalNames_ThenReturnsMergedUniqueNames)
{
    ASSERT_TRUE(library_.createPlaylist("Workout"));

    EXPECT_CALL(mockRepository_, listNames())
        .Times(1)
        .WillOnce(Return(std::vector<std::string>{"Workout", "Travel"}));

    std::vector<std::string> playlistNames = library_.getAllPlaylistNames();

    EXPECT_EQ(playlistNames.size(), 2);
    EXPECT_NE(std::find(playlistNames.begin(), playlistNames.end(), "Workout"), playlistNames.end());
    EXPECT_NE(std::find(playlistNames.begin(), playlistNames.end(), "Travel"), playlistNames.end());
}

TEST_F(PlaylistLibraryTest, SavePlaylist_WhenPlaylistExists_ThenCallsRepositorySaveAndReturnsTrue)
{
    ASSERT_TRUE(library_.createPlaylist("Workout"));

    EXPECT_CALL(mockRepository_, save(_))
        .Times(1)
        .WillOnce(Return(true));

    bool result = library_.savePlaylist("Workout");

    EXPECT_TRUE(result);
}

TEST_F(PlaylistLibraryTest, SavePlaylist_WhenPlaylistDoesNotExist_ThenReturnsFalse)
{
    EXPECT_CALL(mockRepository_, save(_)).Times(0);

    bool result = library_.savePlaylist("Unknown");

    EXPECT_FALSE(result);
}

TEST_F(PlaylistLibraryTest, LoadPlaylist_WhenRepositoryLoadSucceeds_ThenStoresLoadedPlaylistInLibrary)
{
    EXPECT_CALL(mockRepository_, load("Workout", _))
        .Times(1)
        .WillOnce(Invoke(
            [](const std::string&, IPlaylist& playlist)
            {
                playlist.clear();
                playlist.setName("Workout");
                playlist.addSong(Song("1", "Believer", "Imagine Dragons", 204, "resources/audio/song1.wav"));
                return true;
            }));

    bool result = library_.loadPlaylist("Workout");

    EXPECT_TRUE(result);

    IPlaylist* loadedPlaylist = library_.getPlaylist("Workout");
    ASSERT_NE(loadedPlaylist, nullptr);
    EXPECT_EQ(loadedPlaylist->getName(), "Workout");
    EXPECT_EQ(loadedPlaylist->getSongCount(), 1);
}

TEST_F(PlaylistLibraryTest, LoadPlaylist_WhenRepositoryLoadFails_ThenReturnsFalse)
{
    EXPECT_CALL(mockRepository_, load("Workout", _))
        .Times(1)
        .WillOnce(Return(false));

    bool result = library_.loadPlaylist("Workout");

    EXPECT_FALSE(result);
    EXPECT_EQ(library_.getPlaylist("Workout"), nullptr);
}

TEST_F(PlaylistLibraryTest, LoadAvailableSongs_WhenFileContainsValidSongs_ThenLoadsAllSongs)
{
    std::ofstream outputFile(tempSongsFilePath_);
    outputFile << "1,Believer,Imagine Dragons,204,resources/audio/song1.wav\n";
    outputFile << "2,Numb,Linkin Park,185,resources/audio/song2.wav\n";
    outputFile.close();

    bool result = library_.loadAvailableSongs(tempSongsFilePath_.string());

    EXPECT_TRUE(result);
    EXPECT_EQ(library_.getAvailableSongs().size(), 2);

    const Song* foundSong = library_.findAvailableSongById("2");
    ASSERT_NE(foundSong, nullptr);
    EXPECT_EQ(foundSong->getTitle(), "Numb");
    EXPECT_EQ(foundSong->getArtist(), "Linkin Park");
}

TEST_F(PlaylistLibraryTest, LoadAvailableSongs_WhenFileContainsInvalidDuration_ThenSkipsInvalidSongAndLoadsValidSongs)
{
    std::ofstream outputFile(tempSongsFilePath_);
    outputFile << "1,Believer,Imagine Dragons,204,resources/audio/song1.wav\n";
    outputFile << "2,Numb,Linkin Park,abc,resources/audio/song2.wav\n";
    outputFile.close();

    bool result = library_.loadAvailableSongs(tempSongsFilePath_.string());

    EXPECT_TRUE(result);
    EXPECT_EQ(library_.getAvailableSongs().size(), 1);

    const Song* validSong = library_.findAvailableSongById("1");
    const Song* invalidSong = library_.findAvailableSongById("2");

    EXPECT_NE(validSong, nullptr);
    EXPECT_EQ(invalidSong, nullptr);
}

TEST_F(PlaylistLibraryTest, LoadAvailableSongs_WhenFileCannotBeOpened_ThenReturnsFalse)
{
    bool result = library_.loadAvailableSongs("file_that_does_not_exist.txt");

    EXPECT_FALSE(result);
    EXPECT_TRUE(library_.getAvailableSongs().empty());
}

TEST_F(PlaylistLibraryTest, FindAvailableSongById_WhenSongExists_ThenReturnsSongPointer)
{
    std::ofstream outputFile(tempSongsFilePath_);
    outputFile << "1,Believer,Imagine Dragons,204,resources/audio/song1.wav\n";
    outputFile << "2,Numb,Linkin Park,185,resources/audio/song2.wav\n";
    outputFile.close();

    ASSERT_TRUE(library_.loadAvailableSongs(tempSongsFilePath_.string()));

    const Song* foundSong = library_.findAvailableSongById("1");

    ASSERT_NE(foundSong, nullptr);
    EXPECT_EQ(foundSong->getTitle(), "Believer");
}

TEST_F(PlaylistLibraryTest, FindAvailableSongById_WhenSongDoesNotExist_ThenReturnsNullptr)
{
    std::ofstream outputFile(tempSongsFilePath_);
    outputFile << "1,Believer,Imagine Dragons,204,resources/audio/song1.wav\n";
    outputFile.close();

    ASSERT_TRUE(library_.loadAvailableSongs(tempSongsFilePath_.string()));

    const Song* foundSong = library_.findAvailableSongById("999");

    EXPECT_EQ(foundSong, nullptr);
}
