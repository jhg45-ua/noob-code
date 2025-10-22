//
// Created by Julián Hinojosa Gil on 19/5/24.
//

#include "Agency.h"

using namespace std;

Agency::Agency(std::string name, double initialMoney)
{
    Agency::name = name;
    Agency::money = initialMoney;
    Agency::influencers;
}

Influencer *Agency::searchInfluencer(std::string infName)
{
    for (Influencer &influencer : influencers)
    {
        if (influencer.getName() == infName)
            return &influencer;
    }
    throw EXCEPTION_INFL_NOT_FOUND;
}

void Agency::addInfluencer(std::string infName, double commission)
{
    try
    {
        searchInfluencer(infName);

        Util::error(ERR_DUPLICATED);
    }
    catch (const Exception &e)
    {
        try
        {
            Influencer newInfluencer(infName);
            newInfluencer.setCommission(commission);
            influencers.push_back(newInfluencer);
        }
        catch (const Exception &e)
        {
            Util::error(ERR_WRONG_COMMISSION);
        }
    }
}

void Agency::addFollowers(std::string infName, std::string snName, int nFollowers)
{
    try
    {
        Influencer *influencer = searchInfluencer(infName);

        influencer->addFollowers(snName, nFollowers);
    }
    catch (const Exception &e)
    {
        Util::error(ERR_NOT_FOUND);
    }
}

void Agency::newEvent(vector<std::string> infNames, int nsns, std::string *snNames, double *evtRatings)
{
    for (const auto &infName : infNames)
    {
        Influencer *realInf = nullptr;

        try
        {
            realInf = searchInfluencer(infName);
        }
        catch (const Exception &e)
        {
            realInf = nullptr;
        }

        if (realInf != nullptr)
            realInf->addEvent(nsns, snNames, evtRatings);
    }
}

void Agency::deleteInfluencer(std::string infName)
{
    Influencer *realInf = nullptr;

    try
    {
        realInf = searchInfluencer(infName);
    }
    catch (const Exception &e)
    {
        Util::error(ERR_NOT_FOUND);
        return;
    }

    Agency::money += realInf->collectCommission();

    for (int i = 0; i < (int)influencers.size(); i++)
    {
        if (influencers[i].getName() == realInf->getName())
        {
            delete realInf;
            influencers.erase(influencers.begin() + i);
        }
    }
}

double Agency::collectCommissions()
{
    double totalComm = 0.0;

    for (int i = 0; i < (int)influencers.size(); i++)
        totalComm += influencers[i].collectCommission();

    Agency::money += totalComm;
    return totalComm;
}

ostream &operator<<(ostream &os, const Agency &ag)
{
    os << "Agency: " << ag.getName() << "[" << ag.getMoney() << "]" << endl;
    for (const Influencer &i : ag.influencers)
        os << i;

    os << endl;
    return os;
}