//
// Created by Julián Hinojosa Gil on 2/6/24.
//

#ifndef EXOOP_JUL23_USER_H
#define EXOOP_JUL23_USER_H

#include "Playlist.h"
#include "Song.h"

class User
{
  private:
    unsigned int id;
    string name;
    static unsigned int nextId;
    vector<Playlist> lists;


  public:
    User(string name = "New User");

    bool createPlaylist(string name);
    void addSong(string name, Song* song);

    vector<Playlist> getPlaylist() const { return lists; };
};



#endif // EXOOP_JUL23_USER_H
