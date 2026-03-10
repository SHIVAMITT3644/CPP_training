#include "MusicPlaylistApp.h"

#include <iostream>
#include <vector>

#include "Input.h"
#include "Constants.h"

bool isPlaylistSelected(const IPlaylist* playlist)
{
    bool isPlaylistSelected = true;

    if (playlist == nullptr)
    {
        std::cout << NO_PLAYLIST_SELECTED_MESSAGE;
        isPlaylistSelected = false;
    }

    return isPlaylistSelected;
}

int readPlaylistSubMenuChoice()
{
    std::cout << PLAYLIST_SUB_MENU;
    int choice = readValidUserInput(ENTER_CHOICE_MESSAGE);

    return choice;
}

std::string readPlaylistName()
{
    std::string playlistName;
    readCompleteLineInput(std::cin, playlistName, ENTER_PLAYLIST_NAME_MESSAGE);

    return playlistName;
}

std::string readSongId(const std::string& message)
{
    std::string songId;
    readCompleteLineInput(std::cin, songId, message);

    return songId;
}

void showMainMenu()
{
    std::cout << MAIN_MENU;
}

void showPlaylistMenu(const IPlaylist* playlist)
{
    std::cout << PLAYLIST_MENU;
    std::cout << PLAYLIST_NAME_LABEL << playlist->getName() << "\n";
}

void showAvailableSongs(const PlaylistLibrary& library, const IPlaylist* selectedPlaylist)
{
    const std::vector<Song>& songs = library.getAvailableSongs();
    bool hasAvailableSongToAdd = false;

    for (const Song& song : songs)
    {
        if (!selectedPlaylist->hasSongId(song.getId()))
        {
            hasAvailableSongToAdd = true;
            break;
        }
    }

    if (!hasAvailableSongToAdd)
    {
        std::cout << "No songs available to add.\n";
    }
    else
    {
        std::cout << AVAILABLE_SONGS_HEADER;
        std::cout << SONG_TABLE_LINE;
        std::cout << AVAILABLE_SONGS_TABLE_HEADER;
        std::cout << SONG_TABLE_LINE;

        for (const Song& song : songs)
        {
            if (!selectedPlaylist->hasSongId(song.getId()))
            {
                std::cout << song.getId() << " | "
                          << song.getTitle() << " | "
                          << song.getArtist() << " | "
                          << song.getDurationInSeconds() << "\n";
            }
        }

        std::cout << SONG_TABLE_LINE;
    }
}

void showAllSongs(const IPlaylist* playlist)
{
    if (isPlaylistSelected(playlist))
    {
        const std::vector<Song>& songs = playlist->getSongs();

        if (songs.empty())
        {
            std::cout << PLAYLIST_EMPTY_MESSAGE;
        }
        else
        {
            int currentSongIndex = playlist->getCurrentSongIndex();

            std::cout << PLAYLIST_SONGS_HEADER;
            std::cout << SONG_TABLE_LINE;
            std::cout << AVAILABLE_SONGS_TABLE_HEADER;
            std::cout << SONG_TABLE_LINE;

            for (int index = 0; index < static_cast<int>(songs.size()); index++)
            {
                std::cout << songs[index].getId() << " | "
                          << songs[index].getTitle() << " | "
                          << songs[index].getArtist() << " | "
                          << songs[index].getDurationInSeconds();

                if (index == currentSongIndex)
                {
                    std::cout << CURRENT_SONG_LABEL;
                }

                std::cout << "\n";
            }

            std::cout << SONG_TABLE_LINE;
        }
    }
}

void showAllPlaylists(PlaylistLibrary& library)
{
    std::vector<std::string> playlistNames = library.getAllPlaylistNames();

    if (playlistNames.empty())
    {
        std::cout << NO_PLAYLISTS_AVAILABLE_MESSAGE;
    }
    else
    {
        std::cout << PLAYLISTS_HEADER;

        for (size_t index = 0; index < playlistNames.size(); index++)
        {
            std::cout << index + 1 << ". " << playlistNames[index] << "\n";
        }
    }
}

void exitProgram(PlayerController& controller, IPlaylist*& selectedPlaylist, bool& isRunning)
{
    controller.stop();
    controller.setActivePlaylist(nullptr);
    selectedPlaylist = nullptr;
    isRunning = false;

    std::cout << EXIT_PROGRAM_MESSAGE;
}

void playSong(PlayerController& controller)
{
    if (!controller.play())
    {
        std::cout << UNABLE_TO_PLAY_SONG_MESSAGE;
    }
}

void pauseSong(PlayerController& controller)
{
    if (!controller.pause())
    {
        std::cout << UNABLE_TO_PAUSE_SONG_MESSAGE;
    }
}

void stopSong(PlayerController& controller)
{
    if (!controller.stop())
    {
        std::cout << UNABLE_TO_STOP_SONG_MESSAGE;
    }
}

void nextSong(PlayerController& controller)
{
    if (!controller.next())
    {
        std::cout << NO_NEXT_SONG_MESSAGE;
    }
}

void previousSong(PlayerController& controller)
{
    if (!controller.previous())
    {
        std::cout << NO_PREVIOUS_SONG_MESSAGE;
    }
}

void handleCreatePlaylistResult(bool isPlaylistCreated, bool isPlaylistSaved, bool& isCreateMenuRunning)
{
    if (isPlaylistCreated)
    {
        if (isPlaylistSaved)
        {
            std::cout << PLAYLIST_CREATED_AND_SAVED_MESSAGE;
        }
        else
        {
            std::cout << PLAYLIST_CREATED_MEMORY_ONLY_MESSAGE;
        }

        isCreateMenuRunning = false;
    }
    else
    {
        std::cout << PLAYLIST_ALREADY_EXISTS_MESSAGE;
    }
}

bool createAndSavePlaylist(PlaylistLibrary& library, bool& isCreateMenuRunning)
{
    bool isHandledSuccessfully = false;
    std::string playlistName = readPlaylistName();

    bool isPlaylistCreated = library.createPlaylist(playlistName);
    bool isPlaylistSaved = false;

    if (isPlaylistCreated)
    {
        isPlaylistSaved = library.savePlaylist(playlistName);
        isHandledSuccessfully = true;
    }

    handleCreatePlaylistResult(isPlaylistCreated,
                               isPlaylistSaved,
                               isCreateMenuRunning);

    return isHandledSuccessfully;
}

void createPlaylist(PlaylistLibrary& library)
{
    bool isCreateMenuRunning = true;

    while (isCreateMenuRunning)
    {
        int choice = readPlaylistSubMenuChoice();

        switch (choice)
        {
        case 1:
            createAndSavePlaylist(library, isCreateMenuRunning);
            break;

        case 2:
            isCreateMenuRunning = false;
            break;

        default:
            std::cout << INVALID_CHOICE_MESSAGE;
            break;
        }
    }
}

void clearSelectedPlaylistForDeletion(const std::string& playlistName, IPlaylist*& selectedPlaylist, PlayerController& controller)
{
    if (selectedPlaylist != nullptr && selectedPlaylist->getName() == playlistName)
    {
        controller.stop();
        controller.setActivePlaylist(nullptr);
        selectedPlaylist = nullptr;
    }
}

void handleDeletePlaylistResult(bool isPlaylistDeleted, bool& isDeleteMenuRunning)
{
    if (isPlaylistDeleted)
    {
        std::cout << PLAYLIST_DELETED_MESSAGE;
        isDeleteMenuRunning = false;
    }
    else
    {
        std::cout << PLAYLIST_NOT_FOUND_MESSAGE;
    }
}

bool deleteSelectedPlaylist(PlaylistLibrary& library, IPlaylist*& selectedPlaylist, PlayerController& controller, bool& isDeleteMenuRunning)
{
    bool isPlaylistDeleted = false;
    std::string playlistName = readPlaylistName();

    clearSelectedPlaylistForDeletion(playlistName, selectedPlaylist, controller);

    isPlaylistDeleted = library.deletePlaylist(playlistName);

    handleDeletePlaylistResult(isPlaylistDeleted, isDeleteMenuRunning);

    return isPlaylistDeleted;
}

void deletePlaylist(PlaylistLibrary& library, IPlaylist*& selectedPlaylist, PlayerController& controller)
{
    bool isDeleteMenuRunning = true;

    while (isDeleteMenuRunning)
    {
        int choice = readPlaylistSubMenuChoice();

        switch (choice)
        {
        case 1:
            deleteSelectedPlaylist(library, selectedPlaylist, controller, isDeleteMenuRunning);
            break;

        case 2:
            isDeleteMenuRunning = false;
            break;

        default:
            std::cout << INVALID_CHOICE_MESSAGE;
            break;
        }
    }
}

IPlaylist* getOrLoadPlaylist(PlaylistLibrary& library, const std::string& playlistName)
{
    IPlaylist* playlist = library.getPlaylist(playlistName);

    if (playlist == nullptr)
    {
        bool isPlaylistLoaded = library.loadPlaylist(playlistName);

        if (isPlaylistLoaded)
        {
            playlist = library.getPlaylist(playlistName);
        }
    }

    return playlist;
}

void activatePlaylist(IPlaylist* playlist, IPlaylist*& selectedPlaylist, PlayerController& controller)
{
    selectedPlaylist = playlist;
    controller.setActivePlaylist(selectedPlaylist);
}

bool hasSongAvailableToAdd(const PlaylistLibrary& library, const IPlaylist* selectedPlaylist)
{
    bool hasAvailableSongToAdd = false;
    const std::vector<Song>& songs = library.getAvailableSongs();

    for (const Song& song : songs)
    {
        if (!selectedPlaylist->hasSongId(song.getId()))
        {
            hasAvailableSongToAdd = true;
            break;
        }
    }

    return hasAvailableSongToAdd;
}

void handleAddSongResult(const Song* selectedSong, IPlaylist* selectedPlaylist, PlaylistLibrary& library)
{
    if (selectedSong == nullptr)
    {
        std::cout << SONG_ID_NOT_FOUND_MESSAGE;
    }
    else if (selectedPlaylist->hasSongId(selectedSong->getId()))
    {
        std::cout << SONG_ID_ALREADY_EXISTS_MESSAGE;
    }
    else if (selectedPlaylist->addSong(*selectedSong))
    {
        library.savePlaylist(selectedPlaylist->getName());
        std::cout << SONG_ADDED_MESSAGE;
    }
    else
    {
        std::cout << UNABLE_TO_ADD_SONG_MESSAGE;
    }
}

void addSong(IPlaylist* selectedPlaylist, PlaylistLibrary& library)
{
    if (isPlaylistSelected(selectedPlaylist))
    {
        if (library.getAvailableSongs().empty())
        {
            std::cout << NO_SONGS_IN_RESOURCES_ERROR_MESSAGE;
        }
        else if (!hasSongAvailableToAdd(library, selectedPlaylist))
        {
            std::cout << SONG_UNAVAILABLE_ERROR_MESSAGE;
        }
        else
        {
            showAvailableSongs(library, selectedPlaylist);

            std::string songId = readSongId(ENTER_SONG_ID_TO_ADD_MESSAGE);
            const Song* selectedSong = library.findAvailableSongById(songId);

            handleAddSongResult(selectedSong, selectedPlaylist, library);
        }
    }
}

bool isCurrentSongBeingRemoved(const IPlaylist* selectedPlaylist, const std::string& songId)
{
    bool isRemovingCurrentSong = false;
    const Song* currentSong = selectedPlaylist->getCurrentSong();

    if (currentSong != nullptr && currentSong->getId() == songId)
    {
        isRemovingCurrentSong = true;
    }

    return isRemovingCurrentSong;
}

void stopPlayerIfRemovingCurrentSong(bool isRemovingCurrentSong, PlayerController& controller)
{
    if (isRemovingCurrentSong)
    {
        controller.stop();
    }
}

void handleRemoveSongResult(bool isSongRemoved, IPlaylist* selectedPlaylist, PlaylistLibrary& library)
{
    if (isSongRemoved)
    {
        library.savePlaylist(selectedPlaylist->getName());
        std::cout << SONG_REMOVED_MESSAGE;
    }
    else
    {
        std::cout << SONG_NOT_FOUND_MESSAGE;
    }
}

void removeSong(IPlaylist* selectedPlaylist, PlayerController& controller, PlaylistLibrary& library)
{
    if (isPlaylistSelected(selectedPlaylist))
    {
        if (selectedPlaylist->getSongCount() == 0)
        {
            std::cout << PLAYLIST_EMPTY_MESSAGE;
        }
        else
        {
            showAllSongs(selectedPlaylist);

            std::string songId = readSongId(ENTER_SONG_ID_TO_REMOVE_MESSAGE);
            bool isRemovingCurrentSong = isCurrentSongBeingRemoved(selectedPlaylist, songId);

            stopPlayerIfRemovingCurrentSong(isRemovingCurrentSong, controller);

            bool isSongRemoved = selectedPlaylist->removeSongById(songId);

            handleRemoveSongResult(isSongRemoved, selectedPlaylist, library);
        }
    }
}

int findSongIndexById(const IPlaylist* playlist, const std::string& songId)
{
    int songIndex = -1;
    const std::vector<Song>& songs = playlist->getSongs();

    for (size_t index = 0; index < songs.size(); index++)
    {
        if (songs[index].getId() == songId)
        {
            songIndex = static_cast<int>(index);
            break;
        }
    }

    return songIndex;
}

void handleMoveSongResult(bool isSongMoved, IPlaylist* playlist, PlaylistLibrary& library, const std::string& successMessage, const std::string& failureMessage)
{
    if (isSongMoved)
    {
        library.savePlaylist(playlist->getName());
        std::cout << successMessage;
    }
    else
    {
        std::cout << failureMessage;
    }
}

void moveSong(IPlaylist* playlist,  PlaylistLibrary& library,  const std::string& inputMessage,  const std::string& successMessage,  const std::string& failureMessage,  bool isMoveUpOperation)
{
    if (isPlaylistSelected(playlist))
    {
        if (playlist->getSongCount() == 0)
        {
            std::cout << PLAYLIST_EMPTY_MESSAGE;
        }
        else
        {
            showAllSongs(playlist);

            std::string songId = readSongId(inputMessage);
            int songIndex = findSongIndexById(playlist, songId);

            if (songIndex == -1)
            {
                std::cout << SONG_NOT_FOUND_MESSAGE;
            }
            else
            {
                bool isSongMoved = false;

                if (isMoveUpOperation)
                {
                    isSongMoved = playlist->moveSongUp(songIndex);
                }
                else
                {
                    isSongMoved = playlist->moveSongDown(songIndex);
                }

                handleMoveSongResult(isSongMoved, playlist, library, successMessage, failureMessage);
            }
        }
    }
}

void moveSongUp(IPlaylist* playlist, PlaylistLibrary& library)
{
    moveSong(playlist, library, ENTER_SONG_ID_TO_MOVE_UP_MESSAGE, SONG_MOVED_UP_SUCCESS_MESSAGE, CANNOT_MOVE_SONG_UP_MESSAGE, true);
}

void moveSongDown(IPlaylist* playlist, PlaylistLibrary& library)
{
    moveSong(playlist, library, ENTER_SONG_ID_TO_MOVE_DOWN_MESSAGE, SONG_MOVED_DOWN_SUCCESS_MESSAGE, CANNOT_MOVE_SONG_DOWN_MESSAGE, false);
}

void handlePlaylistMenuChoice(int choice, bool& isPlaylistMenuRunning, PlaylistLibrary& library, PlayerController& controller, IPlaylist*& selectedPlaylist)
{
    switch (choice)
    {
    case 1:
        addSong(selectedPlaylist, library);
        break;

    case 2:
        removeSong(selectedPlaylist, controller, library);
        break;

    case 3:
        playSong(controller);
        break;

    case 4:
        pauseSong(controller);
        break;

    case 5:
        stopSong(controller);
        break;

    case 6:
        nextSong(controller);
        break;

    case 7:
        previousSong(controller);
        break;

    case 8:
        moveSongUp(selectedPlaylist, library);
        break;

    case 9:
        moveSongDown(selectedPlaylist, library);
        break;

    case 10:
        showAllSongs(selectedPlaylist);
        break;

    case 11:
        controller.stop();
        controller.setActivePlaylist(nullptr);
        selectedPlaylist = nullptr;
        isPlaylistMenuRunning = false;
        std::cout << CLOSED_PLAYLIST_MESSAGE;
        break;

    default:
        std::cout << INVALID_CHOICE_MESSAGE;
        break;
    }
}

void runPlaylistMenu(PlaylistLibrary& library, PlayerController& controller, IPlaylist*& selectedPlaylist)
{
    bool isPlaylistMenuRunning = true;

    while (isPlaylistMenuRunning)
    {
        showPlaylistMenu(selectedPlaylist);
        int choice = readValidUserInput(ENTER_CHOICE_MESSAGE);
        handlePlaylistMenuChoice(choice, isPlaylistMenuRunning, library, controller, selectedPlaylist);
    }
}

void handleOpenPlaylistResult(IPlaylist* playlist, bool& isOpenMenuRunning)
{
    if (playlist != nullptr)
    {
        isOpenMenuRunning = false;
    }
    else
    {
        std::cout << PLAYLIST_NOT_FOUND_MESSAGE;
    }
}

void openPlaylist(PlaylistLibrary& library, PlayerController& controller, IPlaylist*& selectedPlaylist)
{
    bool isOpenMenuRunning = true;

    while (isOpenMenuRunning)
    {
        int choice = readPlaylistSubMenuChoice();

        if (choice == 1)
        {
            std::string playlistName = readPlaylistName();
            IPlaylist* playlist = getOrLoadPlaylist(library, playlistName);

            if (playlist != nullptr)
            {
                activatePlaylist(playlist, selectedPlaylist, controller);
                runPlaylistMenu(library, controller, selectedPlaylist);
            }

            handleOpenPlaylistResult(playlist, isOpenMenuRunning);
        }
        else if (choice == 2)
        {
            isOpenMenuRunning = false;
        }
        else
        {
            std::cout << INVALID_CHOICE_MESSAGE;
        }
    }
}

void handleMainMenuChoice(int choice, bool& isRunning, PlaylistLibrary& library, PlayerController& controller, IPlaylist*& selectedPlaylist)
{
    switch (choice)
    {
    case 1:
        createPlaylist(library);
        break;

    case 2:
        deletePlaylist(library, selectedPlaylist, controller);
        break;

    case 3:
        openPlaylist(library, controller, selectedPlaylist);
        break;

    case 4:
        showAllPlaylists(library);
        break;

    case 5:
        exitProgram(controller, selectedPlaylist, isRunning);
        break;

    default:
        std::cout << INVALID_CHOICE_MESSAGE;
        break;
    }
}

void runApplication(PlaylistLibrary& library, PlayerController& controller)
{
    bool isRunning = true;
    IPlaylist* selectedPlaylist = nullptr;

    std::cout << WELCOME_MESSAGE;

    while (isRunning)
    {
        showMainMenu();

        int choice = readValidUserInput(ENTER_CHOICE_MESSAGE);

        handleMainMenuChoice(choice, isRunning, library, controller, selectedPlaylist);
    }
}
