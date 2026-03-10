#include <iostream>

#include "FilePlaylist.h"
#include "PlaylistLibrary.h"
#include "PlayerController.h"
#include "SfmlAudioPlayer.h"
#include "MusicPlaylistApp.h"
#include "Constants.h"

int main()
{
    FilePlaylistRepository playlistRepository;
    PlaylistLibrary playlistLibrary(playlistRepository);

    if (playlistLibrary.loadAvailableSongs(AVAILABLE_SONGS_FILE_PATH))
    {
        SfmlAudioPlayer audioPlayer;
        PlayerController playerController(audioPlayer);

        runApplication(playlistLibrary, playerController);
    }
    else
    {
        std::cout << FAILED_TO_LOAD_SONGS_MESSAGE;
    }

    return 0;
}