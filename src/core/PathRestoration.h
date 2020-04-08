//
// Created by lida on 2020/3/31.
//

#ifndef ROADRECOVERY98_PATHRESTORATION_H
#define ROADRECOVERY98_PATHRESTORATION_H


#include <string>
#include <list>
#include <map>

class PathRestoration {

public:

    int pathRestorationMethod(
            const std::list<std::string>& GantryIdList,
            const std::string& basicDataPath,
            double modifyCost,
            double addCost,
            double deleteCost,
            double deleteEndCost,
            double deleteCost2,
            std::list<std::map<std::string, std::string> >& GantryListMap);

};


#endif //ROADRECOVERY98_PATHRESTORATION_H
