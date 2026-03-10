#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

constexpr const char* MAIN_MENU =
    "\n========== MAIN MENU ==========\n"
    "1. Create Playlist\n"
    "2. Delete Playlist\n"
    "3. Open Playlist\n"
    "4. View All Playlists\n"
    "5. Exit\n"
    "===============================\n";

constexpr const char* PLAYLIST_SUB_MENU =
    "\n=======================\n"
    "1. Enter playlist name\n"
    "2. Exit\n";

constexpr const char* PLAYLIST_MENU =
    "\n====== PLAYLIST MENU ======\n"
    "1. Add Song\n"
    "2. Remove Song\n"
    "3. Play Song\n"
    "4. Pause Song\n"
    "5. Stop Song\n"
    "6. Next Song\n"
    "7. Previous Song\n"
    "8. Move Song Up\n"
    "9. Move Song Down\n"
    "10. Show All Songs\n"
    "11. Exit Playlist\n"
    "===========================\n";

constexpr const char* WELCOME_MESSAGE = "Welcome to Playlist Manager\n";
constexpr const char* EXIT_PROGRAM_MESSAGE = "Exiting program...\n";
constexpr const char* CLOSED_PLAYLIST_MESSAGE = "Closed playlist.\n";

constexpr const char* PLAYLIST_FILE_PATH = "resources/playlists/";
constexpr const char* TEXT_FILE_EXTENSION  = ".txt";

constexpr const char* ENTER_CHOICE_MESSAGE = "Enter your choice: ";
constexpr const char* ENTER_PLAYLIST_NAME_MESSAGE = "Enter playlist name: ";
constexpr const char* ENTER_PLAYLIST_NAME_TO_DELETE_MESSAGE = "Enter playlist name to delete: ";
constexpr const char* ENTER_SONG_ID_TO_ADD_MESSAGE = "Enter song id to add: ";
constexpr const char* ENTER_SONG_ID_TO_REMOVE_MESSAGE = "Enter song id to remove: ";
constexpr const char* ENTER_SONG_ID_TO_MOVE_UP_MESSAGE = "Enter song id to move up: ";
constexpr const char* ENTER_SONG_ID_TO_MOVE_DOWN_MESSAGE = "Enter song id to move down: ";

constexpr const char* PLAYLIST_NAME_LABEL = "Playlist: ";
constexpr const char* PLAYLISTS_HEADER = "\nPlaylists:\n";
constexpr const char* AVAILABLE_SONGS_HEADER = "\nAvailable Songs\n";
constexpr const char* PLAYLIST_SONGS_HEADER = "\nPlaylist Songs\n";

constexpr const char* SONG_TABLE_LINE = "-------------------------------------------------\n";
constexpr const char* AVAILABLE_SONGS_TABLE_HEADER = "ID | Name | Artist | Duration\n";
constexpr const char* CURRENT_SONG_LABEL = " | CURRENT";
constexpr const char* AVAILABLE_SONGS_FILE_PATH = "resources/songs.txt";
constexpr const char* SONG_UNAVAILABLE_ERROR_MESSAGE = "No songs available.\n";
constexpr const char* NO_SONGS_IN_RESOURCES_ERROR_MESSAGE = "No songs available in resources file.\n";
constexpr const char* NO_PLAYLIST_SELECTED_MESSAGE = "No playlist selected.\n";
constexpr const char* NO_PLAYLISTS_AVAILABLE_MESSAGE = "No playlists available.\n";
constexpr const char* PLAYLIST_EMPTY_MESSAGE = "Playlist empty.\n";

constexpr const char* INVALID_CHOICE_MESSAGE = "Invalid choice.\n";
constexpr const char* POSITIVE_SONG_NUMBER_MESSAGE = "Please enter a positive song number.\n";

constexpr const char* PLAYLIST_CREATED_AND_SAVED_MESSAGE = "Playlist created and saved successfully.\n";
constexpr const char* PLAYLIST_CREATED_MEMORY_ONLY_MESSAGE = "Playlist created in memory but could not be saved.\n";
constexpr const char* PLAYLIST_ALREADY_EXISTS_MESSAGE = "Playlist already exists.\n";
constexpr const char* PLAYLIST_DELETED_MESSAGE = "Playlist deleted.\n";
constexpr const char* PLAYLIST_NOT_FOUND_MESSAGE = "Playlist not found.\n";
constexpr const char* UNABLE_TO_OPEN_PLAYLIST_MESSAGE = "Unable to open playlist.\n";

constexpr const char* SONG_ID_NOT_FOUND_MESSAGE = "Song id not found.\n";
constexpr const char* SONG_ID_ALREADY_EXISTS_MESSAGE = "Song id already exists in playlist.\n";
constexpr const char* SONG_TITLE_ALREADY_EXISTS_MESSAGE = "Song title already exists in playlist.\n";
constexpr const char* SONG_FILE_PATH_ALREADY_EXISTS_MESSAGE = "Song file path already exists in playlist.\n";
constexpr const char* SONG_ADDED_MESSAGE = "Song added.\n";
constexpr const char* UNABLE_TO_ADD_SONG_MESSAGE = "Unable to add song.\n";
constexpr const char* SONG_REMOVED_MESSAGE = "Song removed.\n";
constexpr const char* SONG_NOT_FOUND_MESSAGE = "Song not found.\n";

constexpr const char* UNABLE_TO_PLAY_SONG_MESSAGE = "Unable to play song because empty playlist\n";
constexpr const char* UNABLE_TO_PAUSE_SONG_MESSAGE = "Unable to pause because song is not playing.\n";
constexpr const char* UNABLE_TO_STOP_SONG_MESSAGE = "Unable to stop  because song is not playing.\n";
constexpr const char* NO_NEXT_SONG_MESSAGE = "No next song.\n";
constexpr const char* NO_PREVIOUS_SONG_MESSAGE = "No previous song.\n";
constexpr const char* SONG_MOVED_UP_SUCCESS_MESSAGE = "Song moved up successfully.\n";
constexpr const char* SONG_MOVED_DOWN_SUCCESS_MESSAGE = "Song moved down successfully.\n";
constexpr const char* CANNOT_MOVE_SONG_UP_MESSAGE = "Cannot move song up.\n";
constexpr const char* CANNOT_MOVE_SONG_DOWN_MESSAGE = "Cannot move song down.\n";

constexpr const char* FAILED_TO_LOAD_SONGS_MESSAGE = "Failed to load songs from resources/songs.txt\n";
constexpr const char* INVALID_TIME_DURATION_ERROR_MESSAGE = "Invalid duration value in playlist file.\n";
constexpr const char* INVALID_STRING_INPUT_ERROR_MESSAGE = "\nError: Input cannot be empty. Please try again.\n";
constexpr const char* INVALID_INPUT_ERROR_MESSAGE = "\nError: Please enter a valid Number.\n";

#endif