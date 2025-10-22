//
// Created by Julián Hinojosa Gil on 29/4/24.
//

#include "SNFollowers.h"

using namespace std;

SNFollowers::SNFollowers(string name, int initialFollowers)
{
    if (!SNData::checkSN(name))
        throw EXCEPTION_UNKNOWN_SN;

    if (initialFollowers < 0)
        throw invalid_argument(to_string(initialFollowers));

    SNFollowers::name = name;
    SNFollowers::numFollowers = initialFollowers;
    SNFollowers::money = 0;
}

void SNFollowers::addFollowers(int nf)
{
    numFollowers += nf;

    if (numFollowers < 0)
        numFollowers = 0;
}

void SNFollowers::addEvent(double rating)
{
    if (rating < 0.0)
        throw invalid_argument(to_string(rating));

    double rel = rating/SNData::getAvgRating(name);
    if (rel > 0.8)
    {
        int newFollowers = static_cast<int>(rel * numFollowers);
        numFollowers += newFollowers;
        money = newFollowers * SNData::getAvgMonetizing(name);
    }

    if (rel <= 0.8)
    {
        int newFollowers = static_cast<int>((0.9 - rel) * numFollowers);
        numFollowers -= newFollowers;
    }
}

double SNFollowers::collectCommission(double commission)
{
    if (commission < 0 || commission > 1)
        throw invalid_argument(to_string(commission));

    commission *= money;
    money = 0;

    return commission;
}

ostream& operator<<(ostream &os, const SNFollowers& snf)
{
    os << "[" << snf.name << "|" << snf.numFollowers << "|" << snf.money << "]";
    return os;
}