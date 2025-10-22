//
// Created by Julián Hinojosa Gil on 25/4/24.
//

#ifndef SNDATA_H_
#define SNDATA_H_

#include "Util.h"

using namespace std;

struct SocialNetworkData
{
    string name;
    double averageRating;
    double averageMonetizing;
};

class SNData
{
  private:
    static vector<SocialNetworkData>sns;

  public:
    static void newSocialNetwork(string name, double avrR, double avrM);
    static bool checkSN(string name);
    static double getAvgRating(string name);
    static double getAvgMonetizing(string name);
};

#endif // SNDATA_H_
