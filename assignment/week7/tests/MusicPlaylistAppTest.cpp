#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <string>

#include "MusicPlaylistApp.h"
#include "MockPlaylist.h"
#include "MockPlaylistRepository.h"
#include "MockAudioPlayer.h"
#include "PlaylistLibrary.h"
#include "PlayerController.h"
#include "Playlist.h"
#include "Song.h"

using ::testing::Ref;
using ::testing::Return;
using ::testing::StrEq;

class MusicPlaylistAppTest : public ::testing::Test
{
protected:
    MockPlaylist mockPlaylist_;
};

TEST_F(MusicPlaylistAppTest, IsPlaylistSelected_WhenPlaylistIsNull_ThenReturnsFalse)
{
    const IPlaylist* playlist = nullptr;

    bool result = isPlaylistSelected(playlist);

    EXPECT_FALSE(result);
}

TEST_F(MusicPlaylistAppTest, IsPlaylistSelected_WhenPlaylistIsNotNull_ThenReturnsTrue)
{
    const IPlaylist* playlist = &mockPlaylist_;

    bool result = isPlaylistSelected(playlist);

    EXPECT_TRUE(result);
}

class MusicPlaylistAppLogicTest : public ::testing::Test
{
protected:
    MockAudioPlayer mockAudioPlayer_;
    MockPlaylist mockPlaylist_;
    MockPlaylistRepository mockRepository_;
    PlaylistLibrary library_{mockRepository_};
    PlayerController controller_{mockAudioPlayer_};

    Song song1_{"1", "Believer", "Imagine Dragons", 204, "resources/audio/song1.wav"};
    Song song2_{"2", "Numb", "Linkin Park", 185, "resources/audio/song2.wav"};
    Song song3_{"3", "Faded", "Alan Walker", 212, "resources/audio/song3.wav"};

    std::vector<Song> songs_{song1_, song2_, song3_};
};


TEST_F(MusicPlaylistAppLogicTest, ClearSelectedPlaylistForDeletion_WhenSelectedPlaylistMatchesName_ThenStopsControllerAndClearsPointer)
{
    IPlaylist* selectedPlaylist = &mockPlaylist_;

    EXPECT_CALL(mockPlaylist_, getName())
        .Times(1)
        .WillOnce(Return("shivam"));

    controller_.setActivePlaylist(&mockPlaylist_);

    clearSelectedPlaylistForDeletion("shivam", selectedPlaylist, controller_);

    EXPECT_EQ(selectedPlaylist, nullptr);
    EXPECT_EQ(controller_.getActivePlaylist(), nullptr);
}

TEST_F(MusicPlaylistAppLogicTest, ClearSelectedPlaylistForDeletion_WhenSelectedPlaylistDoesNotMatchName_ThenDoesNotClearPointer)
{
    IPlaylist* selectedPlaylist = &mockPlaylist_;

    EXPECT_CALL(mockPlaylist_, getName())
        .Times(1)
        .WillOnce(Return("other"));

    controller_.setActivePlaylist(&mockPlaylist_);

    clearSelectedPlaylistForDeletion("shivam", selectedPlaylist, controller_);

    EXPECT_EQ(selectedPlaylist, &mockPlaylist_);
    EXPECT_EQ(controller_.getActivePlaylist(), &mockPlaylist_);
}

TEST_F(MusicPlaylistAppLogicTest, GetOrLoadPlaylist_WhenPlaylistAlreadyExistsInMemory_ThenReturnsPlaylistWithoutLoading)
{
    ASSERT_TRUE(library_.createPlaylist("shivam"));

    EXPECT_CALL(mockRepository_, load(::testing::_, ::testing::_)).Times(0);

    IPlaylist* playlist = getOrLoadPlaylist(library_, "shivam");

    ASSERT_NE(playlist, nullptr);
    EXPECT_EQ(playlist->getName(), "shivam");
}

TEST_F(MusicPlaylistAppLogicTest, GetOrLoadPlaylist_WhenPlaylistNotInMemoryButLoadSucceeds_ThenReturnsLoadedPlaylist)
{
    EXPECT_CALL(mockRepository_, load(StrEq("shivam"), ::testing::_))
        .Times(1)
        .WillOnce(::testing::Invoke(
            [](const std::string&, IPlaylist& playlist)
            {
                playlist.clear();
                playlist.setName("shivam");
                return true;
            }));

    IPlaylist* playlist = getOrLoadPlaylist(library_, "shivam");

    ASSERT_NE(playlist, nullptr);
    EXPECT_EQ(playlist->getName(), "shivam");
}

TEST_F(MusicPlaylistAppLogicTest, GetOrLoadPlaylist_WhenPlaylistNotInMemoryAndLoadFails_ThenReturnsNullptr)
{
    EXPECT_CALL(mockRepository_, load(StrEq("shivam"), ::testing::_))
        .Times(1)
        .WillOnce(Return(false));

    IPlaylist* playlist = getOrLoadPlaylist(library_, "shivam");

    EXPECT_EQ(playlist, nullptr);
}

TEST_F(MusicPlaylistAppLogicTest, ActivatePlaylist_WhenCalled_ThenSetsSelectedPlaylistAndControllerActivePlaylist)
{
    IPlaylist* selectedPlaylist = nullptr;

    activatePlaylist(&mockPlaylist_, selectedPlaylist, controller_);

    EXPECT_EQ(selectedPlaylist, &mockPlaylist_);
    EXPECT_EQ(controller_.getActivePlaylist(), &mockPlaylist_);
}
