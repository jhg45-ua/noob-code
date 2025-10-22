//
// Created by Julián Hinojosa Gil on 7/5/24.
//

#ifndef INFLUENCER_H
#define INFLUENCER_H

#include "SNFollowers.h"

using namespace std;

class Influencer
{
    friend ostream &operator<<(ostream &os, const Influencer &inf);

  private:
    string name;
    double commission;
    vector<SNFollowers> followers;

    bool findFollowers(string snName, int &pos);

  public:
    Influencer(string name);

    void setCommission(double commission);
    void addFollowers(string snName, int nfollowers);
    void addEvent(int nsns, string sn[], double rat[]);
    double collectCommission();

    string getName() const { return name; };
    vector<SNFollowers> getFollowers() const { return followers; };
    double getCommission() const { return commission; };
};

#endif // INFLUENCER_H
