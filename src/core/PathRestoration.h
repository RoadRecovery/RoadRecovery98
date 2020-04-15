//
// Created by lida on 2020/3/31.
//

#ifndef ROADRECOVERY98_PATHRESTORATION_H
#define ROADRECOVERY98_PATHRESTORATION_H


#include <string>
#include <list>
#include <map>
#include "../entity/Graph.h"
#include "../entity/RuntimeNode.h"
#include "../tool/ReadExcel.h"

class PathRestoration {

public:

  static ReadExcel readExcel;

  std::string & enStationId;
  std::string & exStationId;
  std::string & enTime;
  std::string & exTime;
  std::string & basicDataPath;

  const std::vector<std::pair<std::string, std::string> > & gantryInputs;

  double addCost, deleteCost, deleteCost2, modifyCost, deleteEndCost;

  PathRestoration(
          std::string & enStationId,
          std::string & enTime,
          std::string & exStationId,
          std::string & exTime,
          std::string & basicDataPath,
          double modifyCost,
          double addCost,
          double deleteCost,
          double deleteCost2,
          double deleteEndCost,
          const std::vector<std::pair<std::string, std::string> > & gantryInputs
      );

  int pathRestorationMethod(std::vector<std::pair<std::string, std::string> > & gantryOutputs);

  bool extractNode(const Graph & ,  std::string&,  std::string& , std::vector<RuntimeNode> *);
};


#endif //ROADRECOVERY98_PATHRESTORATION_H
