//
// Created by Julián Hinojosa Gil on 19/5/24.
//

#ifndef AGENCY_HPP
#define AGENCY_HPP

#include "Influencer.h"

using namespace std;

class Agency
{
    friend ostream& operator<<(ostream &os,const Agency &ag);

  private:
    string name;
    double money;

    vector<Influencer> influencers;
  public:
    Agency(string name, double initialMoney);

    Influencer *searchInfluencer(string infName);
    void addInfluencer(string infName, double commission);
    void addFollowers(string infName, string snName, int nFollowers);
    void newEvent(vector<string> infNames, int nsns, string snNames[], double evtRatings[]);
    void deleteInfluencer(string infName);
    double collectCommissions();

    string getName() const { return name; };
    double getMoney() const { return money; };
};

#endif // AGENCY_HPP