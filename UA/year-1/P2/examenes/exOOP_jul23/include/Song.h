//
// Created by Julián Hinojosa Gil on 2/6/24.
//

#ifndef EXOOP_JUL23_SONG_H
#define EXOOP_JUL23_SONG_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

class Song
{
    friend ostream &operator<<(ostream &os, const Song& song);

  private:
    string name;
    string artist;
    unsigned int duration;

  public:
    Song(string name, string artist, unsigned int dur);

    string getName() const { return name; };
    string getArtist() const { return artist; };
    unsigned int getDuration() const { return duration; };
};

#endif // EXOOP_JUL23_SONG_H
