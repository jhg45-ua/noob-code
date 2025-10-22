//
// Created by Julián Hinojosa Gil on 7/5/24.
//

#include "Influencer.h"

using namespace std;

Influencer::Influencer(std::string name)
{
    Influencer::name = name;
    Influencer::commission = 0.1;
    Influencer::followers;
}

void Influencer::setCommission(double commission)
{
    if (commission < 0 || commission > 0.8)
        throw EXCEPTION_WRONG_COMMISSION;

    Influencer::commission = commission;
}

bool Influencer::findFollowers(string snName, int &pos)
{
    for (int i = 0; i < (int)followers.size(); i++)
    {
        if (followers[i].getName() == snName)
        {
            pos = i;
            return true;
        }

    }
    return false;
}

void Influencer::addFollowers(string snName, int nfollowers)
{
    int pos = 0;
    bool found;

    found = findFollowers(snName, pos);

    if (found)
        followers[pos].addFollowers(nfollowers);
    else
    {
        try
        {
            SNFollowers newFollowers(snName, nfollowers);
            followers.push_back(newFollowers);
        }
        catch (Exception &e)
        {
            Util::error(ERR_UNKNOWN_SN);
            return;
        }
    }
}

void Influencer::addEvent(int nsns, std::string *sn, double *rat)
{
    for (int i = 0; i <= nsns; i++)
    {
        for (int j = 0; j < (int)followers.size(); j++)
        {
            if (followers[j].getName() == sn[i])
            {
                followers[j].addEvent(rat[i]);
            }
        }
    }
}

double Influencer::collectCommission()
{
    double total = 0.0;

    for (int i = 0; i < (int)followers.size(); i++)
    {
        double subTotal = followers[i].collectCommission(commission);
        total += subTotal;
    }

    return total;
}

ostream &operator<<(ostream &os, const Influencer &inf)
{
    os << "Influencer: " << inf.name << " (" << inf.commission << ")" << endl;

    for (const SNFollowers &snf : inf.followers)
        os << snf;

    os << endl;
    return os;
}