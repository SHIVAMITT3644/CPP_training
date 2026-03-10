#include <gtest/gtest.h>
#include "Song.h"

TEST(SongTest, DefaultConstructor_WhenCalled_ThenInitializesMembersWithDefaultValues)
{
    Song song;

    EXPECT_EQ(song.getId(), "");
    EXPECT_EQ(song.getTitle(), "");
    EXPECT_EQ(song.getArtist(), "");
    EXPECT_EQ(song.getDurationInSeconds(), 0);
    EXPECT_EQ(song.getFilePath(), "");
}

TEST(SongTest, ParameterizedConstructor_WhenCalled_ThenInitializesAllMembersCorrectly)
{
    Song song("1",
              "Believer",
              "Imagine Dragons",
              204,
              "resources/audio/song1.wav");

    EXPECT_EQ(song.getId(), "1");
    EXPECT_EQ(song.getTitle(), "Believer");
    EXPECT_EQ(song.getArtist(), "Imagine Dragons");
    EXPECT_EQ(song.getDurationInSeconds(), 204);
    EXPECT_EQ(song.getFilePath(), "resources/audio/song1.wav");
}
