//
// Created by Julián Hinojosa Gil on 29/4/24.
//

#ifndef SNFOLLOWERS_HPP_
#define SNFOLLOWERS_HPP_

#include "Util.h"
#include "SNData.h"
#include <cmath>

using namespace std;

class SNFollowers
{
  private:
    string name;
    int numFollowers;
    double money;

    friend ostream& operator<<(ostream &os, const SNFollowers &snf);

  public:
    SNFollowers(string name, int initialFollowers);

    void addFollowers(int nf);
    void addEvent(double rating);
    double collectCommission(double commission);

    string getName() const { return name; }
    int getNumFollowers() const { return numFollowers; }
    double getMoney() const { return money; }
};

#endif // SNFOLLOWERS_HPP_
