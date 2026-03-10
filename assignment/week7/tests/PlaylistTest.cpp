#include <gtest/gtest.h>
#include "Playlist.h"

class PlaylistTest : public ::testing::Test
{
protected:
    Playlist playlist_{"MyPlaylist"};

    Song song1_{"1", "Believer", "Imagine Dragons", 204, "resources/songs/believer.mp3"};
    Song song2_{"2", "Perfect", "Ed Sheeran", 263, "resources/songs/perfect.mp3"};
    Song song3_{"3", "Shape of You", "Ed Sheeran", 240, "resources/songs/shape_of_you.mp3"};

    void SetUp() override
    {
        playlist_.addSong(song1_);
        playlist_.addSong(song2_);
    }
};

TEST_F(PlaylistTest, DefaultConstructor_WhenCalled_ThenInitializesEmptyPlaylistWithNoCurrentSong)
{
    Playlist playlist;

    EXPECT_EQ(playlist.getName(), "");
    EXPECT_EQ(playlist.getSongCount(), 0);
    EXPECT_EQ(playlist.getCurrentSongIndex(), -1);
    EXPECT_EQ(playlist.getCurrentSong(), nullptr);
}

TEST_F(PlaylistTest, ParameterizedConstructor_WhenCalled_ThenInitializesPlaylistWithProvidedName)
{
    Playlist playlist("MyPlaylist");

    EXPECT_EQ(playlist.getName(), "MyPlaylist");
    EXPECT_EQ(playlist.getSongCount(), 0);
    EXPECT_EQ(playlist.getCurrentSongIndex(), -1);
    EXPECT_EQ(playlist.getCurrentSong(), nullptr);
}

TEST_F(PlaylistTest, SetName_WhenCalled_ThenUpdatesPlaylistName)
{
    playlist_.setName("Road Trip");

    EXPECT_EQ(playlist_.getName(), "Road Trip");
}

TEST_F(PlaylistTest, AddSong_WhenPlaylistAlreadyHasSongs_ThenAddsSongWithoutChangingCurrentIndex)
{
    bool result = playlist_.addSong(song3_);

    EXPECT_TRUE(result);
    EXPECT_EQ(playlist_.getSongCount(), 3);
    EXPECT_EQ(playlist_.getCurrentSongIndex(), 0);
    ASSERT_NE(playlist_.getCurrentSong(), nullptr);
    EXPECT_EQ(playlist_.getCurrentSong()->getId(), "1");
}

TEST_F(PlaylistTest, Clear_WhenPlaylistHasData_ThenRemovesAllSongsAndResetsState)
{
    playlist_.addSong(song3_);
    ASSERT_TRUE(playlist_.setCurrentSongIndex(2));

    playlist_.clear();

    EXPECT_EQ(playlist_.getName(), "");
    EXPECT_EQ(playlist_.getSongCount(), 0);
    EXPECT_EQ(playlist_.getCurrentSongIndex(), -1);
    EXPECT_EQ(playlist_.getCurrentSong(), nullptr);
    EXPECT_TRUE(playlist_.getSongs().empty());
}

TEST_F(PlaylistTest, RemoveSongById_WhenSongDoesNotExist_ThenReturnsFalseAndLeavesPlaylistUnchanged)
{
    playlist_.addSong(song3_);

    bool result = playlist_.removeSongById("999");

    EXPECT_FALSE(result);
    EXPECT_EQ(playlist_.getSongCount(), 3);
    EXPECT_EQ(playlist_.getCurrentSongIndex(), 0);
    ASSERT_NE(playlist_.getCurrentSong(), nullptr);
    EXPECT_EQ(playlist_.getCurrentSong()->getId(), "1");
}

TEST_F(PlaylistTest, RemoveSongById_WhenCurrentSongIsRemoved_ThenUpdatesCurrentSongCorrectly)
{
    playlist_.addSong(song3_);
    ASSERT_TRUE(playlist_.setCurrentSongIndex(1));

    bool result = playlist_.removeSongById("2");

    EXPECT_TRUE(result);
    EXPECT_EQ(playlist_.getSongCount(), 2);
    EXPECT_EQ(playlist_.getCurrentSongIndex(), 1);
    ASSERT_NE(playlist_.getCurrentSong(), nullptr);
    EXPECT_EQ(playlist_.getCurrentSong()->getId(), "3");
}

TEST_F(PlaylistTest, MoveSongUp_WhenIndexIsValid_ThenSwapsSongWithPreviousSong)
{
    playlist_.addSong(song3_);

    bool result = playlist_.moveSongUp(2);

    EXPECT_TRUE(result);
    EXPECT_EQ(playlist_.getSongs()[0].getId(), "1");
    EXPECT_EQ(playlist_.getSongs()[1].getId(), "3");
    EXPECT_EQ(playlist_.getSongs()[2].getId(), "2");
}

TEST_F(PlaylistTest, MoveSongDown_WhenIndexIsValid_ThenSwapsSongWithNextSong)
{
    playlist_.addSong(song3_);

    bool result = playlist_.moveSongDown(0);

    EXPECT_TRUE(result);
    EXPECT_EQ(playlist_.getSongs()[0].getId(), "2");
    EXPECT_EQ(playlist_.getSongs()[1].getId(), "1");
    EXPECT_EQ(playlist_.getSongs()[2].getId(), "3");
}

TEST_F(PlaylistTest, Next_WhenNextSongExists_ThenMovesToNextSong)
{
    playlist_.addSong(song3_);

    bool result = playlist_.next();

    EXPECT_TRUE(result);
    EXPECT_EQ(playlist_.getCurrentSongIndex(), 1);
    ASSERT_NE(playlist_.getCurrentSong(), nullptr);
    EXPECT_EQ(playlist_.getCurrentSong()->getId(), "2");
}

TEST_F(PlaylistTest, Previous_WhenCurrentSongIsNotFirst_ThenMovesToPreviousSong)
{
    playlist_.addSong(song3_);
    ASSERT_TRUE(playlist_.setCurrentSongIndex(2));

    bool result = playlist_.previous();

    EXPECT_TRUE(result);
    EXPECT_EQ(playlist_.getCurrentSongIndex(), 1);
    ASSERT_NE(playlist_.getCurrentSong(), nullptr);
    EXPECT_EQ(playlist_.getCurrentSong()->getId(), "2");
}

TEST_F(PlaylistTest, SetCurrentSongIndex_WhenIndexIsValid_ThenUpdatesCurrentIndex)
{
    playlist_.addSong(song3_);

    bool result = playlist_.setCurrentSongIndex(2);

    EXPECT_TRUE(result);
    EXPECT_EQ(playlist_.getCurrentSongIndex(), 2);
    ASSERT_NE(playlist_.getCurrentSong(), nullptr);
    EXPECT_EQ(playlist_.getCurrentSong()->getId(), "3");
}

TEST_F(PlaylistTest, SetCurrentSongIndex_WhenIndexIsInvalid_ThenReturnsFalseAndLeavesStateUnchanged)
{
    playlist_.addSong(song3_);

    bool result = playlist_.setCurrentSongIndex(5);

    EXPECT_FALSE(result);
    EXPECT_EQ(playlist_.getCurrentSongIndex(), 0);
    ASSERT_NE(playlist_.getCurrentSong(), nullptr);
    EXPECT_EQ(playlist_.getCurrentSong()->getId(), "1");
}

TEST_F(PlaylistTest, HasSongId_WhenSongExists_ThenReturnsTrue)
{
    playlist_.addSong(song3_);

    EXPECT_TRUE(playlist_.hasSongId("2"));
}

TEST_F(PlaylistTest, HasSongTitle_WhenSongDoesNotExist_ThenReturnsFalse)
{
    playlist_.addSong(song3_);

    EXPECT_FALSE(playlist_.hasSongTitle("Unknown Song"));
}

TEST_F(PlaylistTest, HasSongFilePath_WhenSongExists_ThenReturnsTrue)
{
    playlist_.addSong(song3_);

    EXPECT_TRUE(playlist_.hasSongFilePath("resources/songs/perfect.mp3"));
}
