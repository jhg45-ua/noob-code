//
// Created by Julián Hinojosa Gil on 2/6/24.
//

#ifndef EXOOP_JUL23_PLAYLIST_H
#define EXOOP_JUL23_PLAYLIST_H

#include "Song.h"

class Playlist
{
    friend ostream& operator<<(ostream &os, const Playlist& playlist);
  private:
    string name;
    vector<Song*> songs;

  public:
    Playlist(string name);

    unsigned int totalDuration() const;
    void addSong(Song* song);

    string getName() const { return name; };
};

#endif // EXOOP_JUL23_PLAYLIST_H
