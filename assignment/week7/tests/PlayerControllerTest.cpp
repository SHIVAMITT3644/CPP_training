#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "PlayerController.h"
#include "MockAudioPlayer.h"
#include "MockPlaylist.h"

using ::testing::Return;
using ::testing::StrEq;

class PlayerControllerTest : public ::testing::Test
{
protected:
    MockAudioPlayer mockAudioPlayer_;
    MockPlaylist mockPlaylist_;
    PlayerController controller_{mockAudioPlayer_};

    Song song1_{"1", "Believer", "Imagine Dragons", 204, "resources/songs/believer.mp3"};
    Song song2_{"2", "Perfect", "Ed Sheeran", 263, "resources/songs/perfect.mp3"};

    void SetUp() override
    {
        controller_.setActivePlaylist(&mockPlaylist_);
    }
};

TEST_F(PlayerControllerTest, Constructor_WhenCreated_ThenInitializesWithStoppedStateAndNoActivePlaylist)
{
    MockAudioPlayer localMockAudioPlayer;
    PlayerController localController(localMockAudioPlayer);

    EXPECT_EQ(localController.getState(), PlayerController::STOPPED);
    EXPECT_EQ(localController.getActivePlaylist(), nullptr);
}

TEST_F(PlayerControllerTest, SetActivePlaylist_WhenPlaylistChangesWhilePlaying_ThenStopsAudioAndResetsState)
{
    EXPECT_CALL(mockPlaylist_, getCurrentSong())
        .WillOnce(Return(&song1_));
    EXPECT_CALL(mockAudioPlayer_, load(StrEq("resources/songs/believer.mp3")))
        .WillOnce(Return(true));
    EXPECT_CALL(mockAudioPlayer_, play())
        .Times(1);

    EXPECT_TRUE(controller_.play());
    EXPECT_EQ(controller_.getState(), PlayerController::PLAYING);

    MockPlaylist anotherPlaylist;

    EXPECT_CALL(mockAudioPlayer_, stop())
        .Times(1);

    controller_.setActivePlaylist(&anotherPlaylist);

    EXPECT_EQ(controller_.getState(), PlayerController::STOPPED);
    EXPECT_EQ(controller_.getActivePlaylist(), &anotherPlaylist);
}

TEST_F(PlayerControllerTest, Play_WhenNoActivePlaylist_ThenReturnsFalse)
{
    controller_.setActivePlaylist(nullptr);

    EXPECT_FALSE(controller_.play());
    EXPECT_EQ(controller_.getState(), PlayerController::STOPPED);
}

TEST_F(PlayerControllerTest, Play_WhenCurrentSongDoesNotExist_ThenReturnsFalse)
{
    EXPECT_CALL(mockPlaylist_, getCurrentSong())
        .WillOnce(Return(nullptr));

    EXPECT_FALSE(controller_.play());
    EXPECT_EQ(controller_.getState(), PlayerController::STOPPED);
}

TEST_F(PlayerControllerTest, Play_WhenSongIsNotLoadedAndLoadSucceeds_ThenLoadsAndPlaysSong)
{
    EXPECT_CALL(mockPlaylist_, getCurrentSong())
        .WillOnce(Return(&song1_));
    EXPECT_CALL(mockAudioPlayer_, load(StrEq("resources/songs/believer.mp3")))
        .WillOnce(Return(true));
    EXPECT_CALL(mockAudioPlayer_, play())
        .Times(1);

    EXPECT_TRUE(controller_.play());
    EXPECT_EQ(controller_.getState(), PlayerController::PLAYING);
}

TEST_F(PlayerControllerTest, Play_WhenLoadFails_ThenReturnsFalseAndStateRemainsStopped)
{
    EXPECT_CALL(mockPlaylist_, getCurrentSong())
        .WillOnce(Return(&song1_));
    EXPECT_CALL(mockAudioPlayer_, load(StrEq("resources/songs/believer.mp3")))
        .WillOnce(Return(false));

    EXPECT_FALSE(controller_.play());
    EXPECT_EQ(controller_.getState(), PlayerController::STOPPED);
}

TEST_F(PlayerControllerTest, Play_WhenPausedWithSameSong_ThenResumesWithoutLoadingAgain)
{
    EXPECT_CALL(mockPlaylist_, getCurrentSong())
        .WillOnce(Return(&song1_));
    EXPECT_CALL(mockAudioPlayer_, load(StrEq("resources/songs/believer.mp3")))
        .WillOnce(Return(true));
    EXPECT_CALL(mockAudioPlayer_, play())
        .Times(1);

    EXPECT_TRUE(controller_.play());

    EXPECT_CALL(mockAudioPlayer_, pause())
        .Times(1);
    EXPECT_TRUE(controller_.pause());
    EXPECT_EQ(controller_.getState(), PlayerController::PAUSED);

    EXPECT_CALL(mockPlaylist_, getCurrentSong())
        .WillOnce(Return(&song1_));
    EXPECT_CALL(mockAudioPlayer_, play())
        .Times(1);

    EXPECT_TRUE(controller_.play());
    EXPECT_EQ(controller_.getState(), PlayerController::PLAYING);
}

TEST_F(PlayerControllerTest, Play_WhenSameSongIsAlreadyLoadedAndControllerIsStopped_ThenPlaysWithoutLoadingAgain)
{
    EXPECT_CALL(mockPlaylist_, getCurrentSong())
        .WillOnce(Return(&song1_));
    EXPECT_CALL(mockAudioPlayer_, load(StrEq("resources/songs/believer.mp3")))
        .WillOnce(Return(true));
    EXPECT_CALL(mockAudioPlayer_, play())
        .Times(1);

    EXPECT_TRUE(controller_.play());

    EXPECT_CALL(mockAudioPlayer_, stop())
        .Times(1);
    EXPECT_TRUE(controller_.stop());
    EXPECT_EQ(controller_.getState(), PlayerController::STOPPED);

    EXPECT_CALL(mockPlaylist_, getCurrentSong())
        .WillOnce(Return(&song1_));
    EXPECT_CALL(mockAudioPlayer_, play())
        .Times(1);

    EXPECT_TRUE(controller_.play());
    EXPECT_EQ(controller_.getState(), PlayerController::PLAYING);
}

TEST_F(PlayerControllerTest, Pause_WhenStateIsPlaying_ThenPausesAudioAndReturnsTrue)
{
    EXPECT_CALL(mockPlaylist_, getCurrentSong())
        .WillOnce(Return(&song1_));
    EXPECT_CALL(mockAudioPlayer_, load(StrEq("resources/songs/believer.mp3")))
        .WillOnce(Return(true));
    EXPECT_CALL(mockAudioPlayer_, play())
        .Times(1);

    EXPECT_TRUE(controller_.play());

    EXPECT_CALL(mockAudioPlayer_, pause())
        .Times(1);

    EXPECT_TRUE(controller_.pause());
    EXPECT_EQ(controller_.getState(), PlayerController::PAUSED);
}

TEST_F(PlayerControllerTest, Pause_WhenStateIsNotPlaying_ThenReturnsFalse)
{
    EXPECT_FALSE(controller_.pause());
    EXPECT_EQ(controller_.getState(), PlayerController::STOPPED);
}

TEST_F(PlayerControllerTest, Stop_WhenStateIsPlaying_ThenStopsAudioAndReturnsTrue)
{
    EXPECT_CALL(mockPlaylist_, getCurrentSong())
        .WillOnce(Return(&song1_));
    EXPECT_CALL(mockAudioPlayer_, load(StrEq("resources/songs/believer.mp3")))
        .WillOnce(Return(true));
    EXPECT_CALL(mockAudioPlayer_, play())
        .Times(1);

    EXPECT_TRUE(controller_.play());

    EXPECT_CALL(mockAudioPlayer_, stop())
        .Times(1);

    EXPECT_TRUE(controller_.stop());
    EXPECT_EQ(controller_.getState(), PlayerController::STOPPED);
}

TEST_F(PlayerControllerTest, Stop_WhenStateIsPaused_ThenStopsAudioAndReturnsTrue)
{
    EXPECT_CALL(mockPlaylist_, getCurrentSong())
        .WillOnce(Return(&song1_));
    EXPECT_CALL(mockAudioPlayer_, load(StrEq("resources/songs/believer.mp3")))
        .WillOnce(Return(true));
    EXPECT_CALL(mockAudioPlayer_, play())
        .Times(1);

    EXPECT_TRUE(controller_.play());

    EXPECT_CALL(mockAudioPlayer_, pause())
        .Times(1);
    EXPECT_TRUE(controller_.pause());

    EXPECT_CALL(mockAudioPlayer_, stop())
        .Times(1);

    EXPECT_TRUE(controller_.stop());
    EXPECT_EQ(controller_.getState(), PlayerController::STOPPED);
}

TEST_F(PlayerControllerTest, Next_WhenNextSongExistsAndControllerIsPlaying_ThenLoadsNextSongAndPlaysIt)
{
    EXPECT_CALL(mockPlaylist_, getCurrentSong())
        .WillOnce(Return(&song1_));

    EXPECT_CALL(mockAudioPlayer_, load(StrEq("resources/songs/believer.mp3")))
        .WillOnce(Return(true));

    EXPECT_CALL(mockAudioPlayer_, play())
        .Times(1);

    EXPECT_TRUE(controller_.play());
    EXPECT_EQ(controller_.getState(), PlayerController::PLAYING);

    EXPECT_CALL(mockPlaylist_, next())
        .WillOnce(Return(true));

    EXPECT_CALL(mockPlaylist_, getCurrentSong())
        .WillOnce(Return(&song2_));

    EXPECT_CALL(mockAudioPlayer_, load(StrEq("resources/songs/perfect.mp3")))
        .WillOnce(Return(true));

    EXPECT_CALL(mockAudioPlayer_, play())
        .Times(1);

    EXPECT_TRUE(controller_.next());
    EXPECT_EQ(controller_.getState(), PlayerController::PLAYING);
}

TEST_F(PlayerControllerTest, Next_WhenNextSongExistsAndControllerIsPaused_ThenLoadsNextSongAndSetsStateToStopped)
{
    EXPECT_CALL(mockPlaylist_, getCurrentSong())
        .WillOnce(Return(&song1_));
    EXPECT_CALL(mockAudioPlayer_, load(StrEq("resources/songs/believer.mp3")))
        .WillOnce(Return(true));
    EXPECT_CALL(mockAudioPlayer_, play())
        .Times(1);

    EXPECT_TRUE(controller_.play());

    EXPECT_CALL(mockAudioPlayer_, pause())
        .Times(1);
    EXPECT_TRUE(controller_.pause());
    EXPECT_EQ(controller_.getState(), PlayerController::PAUSED);

    EXPECT_CALL(mockPlaylist_, next())
        .WillOnce(Return(true));
    EXPECT_CALL(mockPlaylist_, getCurrentSong())
        .WillOnce(Return(&song2_));
    EXPECT_CALL(mockAudioPlayer_, load(StrEq("resources/songs/perfect.mp3")))
        .WillOnce(Return(true));

    EXPECT_TRUE(controller_.next());
    EXPECT_EQ(controller_.getState(), PlayerController::STOPPED);
}

TEST_F(PlayerControllerTest, Next_WhenPlaylistCannotMoveToNextSong_ThenReturnsFalse)
{
    EXPECT_CALL(mockPlaylist_, next())
        .WillOnce(Return(false));

    EXPECT_FALSE(controller_.next());
}

TEST_F(PlayerControllerTest, Previous_WhenPreviousSongExistsAndControllerIsPlaying_ThenLoadsPreviousSongAndPlaysIt)
{
    EXPECT_CALL(mockPlaylist_, getCurrentSong())
        .WillOnce(Return(&song2_));

    EXPECT_CALL(mockAudioPlayer_, load(StrEq("resources/songs/perfect.mp3")))
        .WillOnce(Return(true));

    EXPECT_CALL(mockAudioPlayer_, play())
        .Times(1);

    EXPECT_TRUE(controller_.play());
    EXPECT_EQ(controller_.getState(), PlayerController::PLAYING);

    EXPECT_CALL(mockPlaylist_, previous())
        .WillOnce(Return(true));

    EXPECT_CALL(mockPlaylist_, getCurrentSong())
        .WillOnce(Return(&song1_));

    EXPECT_CALL(mockAudioPlayer_, load(StrEq("resources/songs/believer.mp3")))
        .WillOnce(Return(true));

    EXPECT_CALL(mockAudioPlayer_, play())
        .Times(1);

    EXPECT_TRUE(controller_.previous());
    EXPECT_EQ(controller_.getState(), PlayerController::PLAYING);
}

TEST_F(PlayerControllerTest, Previous_WhenPlaylistCannotMoveToPreviousSong_ThenReturnsFalse)
{
    EXPECT_CALL(mockPlaylist_, previous())
        .WillOnce(Return(false));

    EXPECT_FALSE(controller_.previous());
}
