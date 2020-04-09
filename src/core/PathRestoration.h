//
// Created by lida on 2020/3/31.
//

#ifndef ROADRECOVERY98_PATHRESTORATION_H
#define ROADRECOVERY98_PATHRESTORATION_H


#include <string>
#include <list>
#include <map>
#include "../entity/Graph.h"

class PathRestoration {

public:

    static Graph graph;

    const std::string & enStationId;
    const std::string & exStationId;
    const std::string & enTime;
    const std::string & exTime;
    const std::string & basicDataPath;

    const std::list<std::string> & gantryIdList;

    double addCost, deleteCost, deleteCost2, modifyCost, deleteEndCost;

    PathRestoration(const std::string & enStationId,
    const std::string & exStationId,
    const std::string & enTime,
    const std::string & exTime,
    const std::string & basicDataPath,
    const std::list<std::string> & gantryIdList);

    int pathRestorationMethod(std::list<std::map<std::string, std::string> > &GantryListMap);
};


#endif //ROADRECOVERY98_PATHRESTORATION_H
