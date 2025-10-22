//
// Created by Julián Hinojosa Gil on 2/6/24.
//

#include "../include/User.h"

unsigned int User::nextId = 1;

User::User(string name)
{
    this->name = name;
    this->id = nextId;
    nextId++;
}

bool User::createPlaylist(string name)
{
    for (int i = 0; i < User::lists.size(); i++)
        if (User::lists[i].getName() == name)
            return false;

    try
    {
        Playlist newList(name);
        lists.push_back(newList);
    } catch (const exception& e)
    {
        cerr << "Error: " << e.what() << endl;
        return false;
    }

    return true;
}

void User::addSong(string name, Song *song)
{
    if (song == nullptr)
        return;

    for (int i = 0; i < User::lists.size(); i++)
    {
        if (User::lists[i].getName() == name)
        {
            User::lists[i].addSong(song);
            return;
        }
    }
}