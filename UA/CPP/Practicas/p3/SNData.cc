//
// Created by Julián Hinojosa Gil on 25/4/24.
//

#include "SNData.h"

using namespace std;

vector<SocialNetworkData> SNData::sns;

void SNData::newSocialNetwork(string name, double avgR, double avgM)
{
    for (size_t i = 0; i < sns.size(); i++)
    {
        if (name == sns[i].name)
            throw invalid_argument(name);
    }
    if (!(avgR > 0 && avgR < 1))
        throw invalid_argument(to_string(avgR));
    if (!(avgM > 0 && avgM < 1))
        throw invalid_argument(to_string(avgM));

    SocialNetworkData netData;
    netData.name = name;
    netData.averageRating = avgR;
    netData.averageMonetizing = avgM;

    sns.push_back(netData);
    // cout << "Datos añadidos al vector" << endl; // debug
}

bool SNData::checkSN(std::string name)
{
    for (size_t i = 0; i < sns.size(); i++)
    {
        if (name == sns[i].name)
        {
            // cout << "Nombre encontrado" << endl; // debug
            return true;
        }
    }
    return false;
}

double SNData::getAvgRating(std::string name)
{
    for (size_t i = 0; i < sns.size(); i++)
    {
        if (name == sns[i].name)
            return sns[i].averageRating;
    }
    return 0.0;
}

double SNData::getAvgMonetizing(std::string name)
{
    for (size_t i = 0; i < sns.size(); i++)
    {
        if (name == sns[i].name)
            return sns[i].averageMonetizing;
    }
    return 0.0;
}