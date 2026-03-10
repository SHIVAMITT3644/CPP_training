#ifndef MUSICPLAYLISTAPP_H
#define MUSICPLAYLISTAPP_H

#include <string>
#include "PlaylistLibrary.h"
#include "PlayerController.h"
#include "IPlaylist.h"

void runApplication(PlaylistLibrary& library, PlayerController& controller);

void createPlaylist(PlaylistLibrary& library);
void deletePlaylist(PlaylistLibrary& library, IPlaylist*& selectedPlaylist, PlayerController& controller);
void openPlaylist(PlaylistLibrary& library, PlayerController& controller, IPlaylist*& selectedPlaylist);

void addSong(IPlaylist* selectedPlaylist, PlaylistLibrary& library);
void removeSong(IPlaylist* selectedPlaylist, PlayerController& controller, PlaylistLibrary& library);

void moveSongUp(IPlaylist* playlist, PlaylistLibrary& library);
void moveSongDown(IPlaylist* playlist, PlaylistLibrary& library);

void showAllSongs(const IPlaylist* playlist);
void clearSelectedPlaylistForDeletion(const std::string& playlistName, IPlaylist*& selectedPlaylist, PlayerController& controller);
IPlaylist* getOrLoadPlaylist(PlaylistLibrary& library, const std::string& playlistName);
void activatePlaylist(IPlaylist* playlist, IPlaylist*& selectedPlaylist, PlayerController& controller);
bool createAndSavePlaylist(PlaylistLibrary& library, bool& isCreateMenuRunning);
bool isPlaylistSelected(const IPlaylist* playlist);

#endif