#include <gtest/gtest.h>
#include "SfmlAudioPlayer.h"

TEST(SfmlAudioPlayerTest, Load_WhenFileDoesNotExist_ThenReturnsFalse)
{
    SfmlAudioPlayer player;

    bool result = player.load("non_existing_audio.wav");

    EXPECT_FALSE(result);
}

TEST(SfmlAudioPlayerTest, Play_WhenCalled_ThenDoesNotThrow)
{
    SfmlAudioPlayer player;

    EXPECT_NO_THROW(player.play());
}

TEST(SfmlAudioPlayerTest, Pause_WhenCalled_ThenDoesNotThrow)
{
    SfmlAudioPlayer player;

    EXPECT_NO_THROW(player.pause());
}

TEST(SfmlAudioPlayerTest, Stop_WhenCalled_ThenDoesNotThrow)
{
    SfmlAudioPlayer player;

    EXPECT_NO_THROW(player.stop());
}
