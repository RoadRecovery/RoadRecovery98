//
// Created by lida on 2020/3/31.
//

#include "PathRestoration.h"
#include "../algorithm/DPAlgorithm.h"
#include <algorithm>
#include <iostream>

ReadExcel PathRestoration::readExcel = ReadExcel();

PathRestoration::PathRestoration(
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
    const std::vector<std::pair<std::string, std::string> > & gantryInputs):
        enStationId(enStationId),
        enTime(enTime),
        exStationId(exStationId),
        exTime(exTime),
        basicDataPath(basicDataPath),
        modifyCost(modifyCost),
        addCost(addCost),
        deleteCost(deleteCost),
        deleteCost2(deleteCost2),
        deleteEndCost(deleteEndCost),
        gantryInputs(gantryInputs)
        {
        }

int PathRestoration::pathRestorationMethod(std::vector<std::pair<std::string, std::string> > & gantryOutputs) {

  if (!readExcel.graph.built) {
//      std::cout << "read graph init." << std::endl;
      readExcel.buildGraph(basicDataPath);
//      std::cout << "read graph done." << std::endl;
  }
  else {
//      std::cout << "graph has already built." << std::endl;
  }

  std::vector<double> configs;
  configs.push_back(modifyCost);
  configs.push_back(addCost);
  configs.push_back(deleteCost);
  configs.push_back(deleteCost2);
  configs.push_back(deleteEndCost);

  std::vector<RuntimeNode> runtimeNodeVector =  std::vector<RuntimeNode>();
  //start node
  if (!extractNode(readExcel.graph, enStationId, enTime, &runtimeNodeVector)) {
      //no entry node.
      return -1;
  }

  //middle gantry list
  std::vector<std::pair<std::string, std::string> >::const_iterator iter;
  for (iter = gantryInputs.begin(); iter != gantryInputs.end(); iter++) {
      std::string firstStr = iter->first;
      std::string secondStr = iter->second;
      if (!extractNode(readExcel.graph, firstStr, secondStr, &runtimeNodeVector)) {
          //no gantry node
          return -1;
      }
  }

  //end node
  if (!extractNode(readExcel.graph, exStationId, exTime, &runtimeNodeVector)) {
      //no exit node.
      return -1;
  }

  RuntimePath runtimePath = RuntimePath(runtimeNodeVector);

  //TODO: handle boundary cases


  //core functionality
//  std::cout << "init DP" << std::endl;
  DPAlgorithm algorithm = DPAlgorithm(runtimePath.runtimeNodeVector.size());
  RuntimePath answerPath;
  algorithm.execute(readExcel.graph, runtimePath, configs, answerPath);
//  std::cout << "DP done" << std::endl;
  answerPath.print("recovered path");

  //TODO: handle the recovered path and dump into gantry outputs


  return 0;
}

bool PathRestoration::extractNode(const Graph & graph, std::string & index, std::string & transTime,
        std::vector<RuntimeNode> * runtimeNodeVector) {
    Node node = Node(index, std::string());
    std::vector<Node>::const_iterator iterator = std::find(graph.nodeVector.begin(),
                                                     graph.nodeVector.end(), node);
    if (iterator == graph.nodeVector.end()) {
        return false;
    }
    RuntimeNode runtimeNode = RuntimeNode(*iterator, transTime);
    runtimeNodeVector->push_back(runtimeNode);
    return true;
}


