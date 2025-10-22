//
// Created by Julián Hinojosa Gil on 2/6/24.
//

#include "../include/Playlist.h"

Playlist::Playlist(std::string name)
{
    if (name.empty())
        throw invalid_argument("Playlist name empty!");

    this->name = name;
}

unsigned int Playlist::totalDuration() const
{
    unsigned int totalDur = 0;
    for (int i = 0; i < Playlist::songs.size(); i++)
        totalDur += Playlist::songs[i]->getDuration();

    return totalDur;
}

void Playlist::addSong(Song *song)
{
    if (song != nullptr)
        songs.push_back(song);
}

ostream& operator<<(ostream &os, const Playlist& playlist)
{
    os << playlist.getName() << endl;
    for (int i = 0; i < playlist.songs.size(); i++)
    {
        os << i+1 << ". " << *playlist.songs[i] << endl; // Recordar que el vector song es de tipo Song*
    }
    os << "- Total duration: " << playlist.totalDuration() << " s";
    return os;
}