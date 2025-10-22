#include <iostream>
#include "../include/User.h"

const string list1 = "Oldies";
int main()
{
    Song *song1 = new Song("Help", "The Beatles", 180);
    Song *song2 = new Song("Hey Jude", "The Beatles", 431);
    Song *song3 = new Song("Tumbling Dice", "The Rolling Stones", 210);
    User user;
    user.createPlaylist(list1);
    user.addSong(list1, song1);
    user.addSong(list1, song2);
    user.addSong(list1, song3);
    vector<Playlist> playlists = user.getPlaylist();
    cout << playlists[0] << endl;
}
