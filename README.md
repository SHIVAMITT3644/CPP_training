Music Playlist Manager (C++)

A console-based Music Playlist Manager built using C++, applying Object Oriented Programming (OOP) principles, STL containers, and unit testing with Google Test and Google Mock.
The application allows users to create and manage playlists, play songs, and persist playlists using file storage.

Features
Playlist Management
Create playlists
Delete playlists
Open existing playlists
View all playlists

Song Management
Add songs to playlist
Remove songs from playlist
Move songs up or down in playlist
View songs in playlist

Audio Playback
Play song
Pause song
Stop song
Next song
Previous song

Persistence
Save playlist to file
Load playlist from file

Testing
Comprehensive unit tests using Google Test
Mocking dependencies using Google Mock

Technologies Used
Standard Template Library (STL)
SFML Audio (for music playback)
Google Test
Google Mock
Filesystem Library

Project Structure
MusicPlaylistManager/
│
├── include/
│   ├── Song.h
│   ├── Playlist.h
│   ├── PlayerController.h
│   ├── PlaylistLibrary.h
│   ├── FilePlaylistRepository.h
│   ├── IPlaylist.h
│   ├── IAudioPlayer.h
│   └── IPlaylistRepository.h
│
├── src/
│   ├── Song.cpp
│   ├── Playlist.cpp
│   ├── PlayerController.cpp
│   ├── PlaylistLibrary.cpp
│   ├── FilePlaylistRepository.cpp
│   ├── SfmlAudioPlayer.cpp
│   └── MusicPlaylistApp.cpp
│
├── tests/
│   ├── SongTest.cpp
│   ├── PlaylistTest.cpp
│   ├── PlaylistLibraryTest.cpp
│   ├── PlayerControllerTest.cpp
│   ├── FilePlaylistRepositoryTest.cpp
│   └── SfmlAudioPlayerTest.cpp
│
├── resources/
│   ├── songs.txt
│   └── audio/
│
└── main.cpp
Build Instructions
Requirements

Install the following dependencies:

Install SFML

sudo apt install libsfml-dev
Install Google Test
sudo apt install libgtest-dev

Compile gtest if required:

cd /usr/src/gtest
sudo cmake .
sudo make
sudo cp lib/*.a /usr/lib
Compile the Project

From the project root directory:
g++ \
src/*.cpp \
tests/*.cpp \
-Iinclude \
-lgtest -lgtest_main -lgmock -lpthread \
-lsfml-audio -lsfml-system \
-o runTests
Run Unit Tests

Run all tests:
./runTests

Run tests with colored output:
./runTests --gtest_color=yes

List all tests:
./runTests --gtest_list_tests

Run specific test suite:
./runTests --gtest_filter=PlaylistTest.*

Run single test:
./runTests --gtest_filter=PlaylistTest.MoveSongUp_WhenIndexIsValid_ThenSwapsSongWithPreviousSong
Example Songs File

Example format of resources/songs.txt:

1,Believer,Imagine Dragons,204,resources/audio/song1.wav
2,Numb,Linkin Park,185,resources/audio/song2.wav

Format:
ID,Title,Artist,DurationInSeconds,FilePath

Design Principles Used
SOLID principles
Dependency Injection
Interface based design
Separation of Concerns
Testable architecture
Testing Coverage

The following components are tested:

Song
Playlist
PlaylistLibrary
PlayerController
FilePlaylistRepository
SfmlAudioPlayer
MusicPlaylistApp (logic only)

Total tests implemented: 64

Example Application Flow
Welcome to Playlist Manager

1. Create Playlist
2. Delete Playlist
3. Open Playlist
4. View All Playlists
5. Exit

Inside playlist menu:

1. Add Song
2. Remove Song
3. Play Song
4. Pause Song
5. Stop Song
6. Next Song
7. Previous Song
8. Move Song Up
9. Move Song Down
10. Show Songs
11. Close Playlist