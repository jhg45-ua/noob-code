//
// Created by Julián Hinojosa Gil on 2/6/24.
//

#include "../include/Song.h"

Song::Song(string name, string artist, unsigned int dur)
{
    if (name.empty())
        throw invalid_argument("Song name empty!");

    if(artist.empty())
        throw invalid_argument("Artist name empty!");

    this->name = name;
    this->artist = artist;
    this->duration = dur;
}

ostream &operator<<(ostream &os, const Song& song)
{
    os << song.getArtist() << " - " << song.getName() << " (" << song.getDuration() << " s)";
    return os;
}
