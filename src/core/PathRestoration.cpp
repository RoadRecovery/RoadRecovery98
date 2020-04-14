//
// Created by lida on 2020/3/31.
//

#include "PathRestoration.h"
#include "../algorithm/DPAlgorithm.h"
#include <algorithm>

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

    //construct data structure that algorithm needs
    ReadExcel readExcel = ReadExcel();
    readExcel.buildGraph(basicDataPath);

    std::vector<double> configs;
    configs.push_back(modifyCost);
    configs.push_back(addCost);
    configs.push_back(deleteCost);
    configs.push_back(deleteCost2);
    configs.push_back(deleteEndCost);

    std::vector<RuntimeNode> runtimeNodeVector =  std::vector<RuntimeNode>();
    //start node
    if (!extractNode(readExcel, enStationId, enTime, &runtimeNodeVector)) {
        //no entry node.
        return -1;
    }

    //middle gantry list
    std::vector<std::pair<std::string, std::string> >::const_iterator iter;
    for (iter = gantryInputs.begin(); iter != gantryInputs.end(); iter++) {
        std::string firstStr = iter->first;
        std::string secondStr = iter->second;
        if (!extractNode(readExcel, firstStr, secondStr, &runtimeNodeVector)) {
            //no gantry node
            return -1;
        }
    }

    //end node
    if (!extractNode(readExcel, exStationId, exTime, &runtimeNodeVector)) {
        //no exit node.
        return -1;
    }

    RuntimePath runtimePath = RuntimePath(runtimeNodeVector);

    //TODO: handle boundary cases


    //core functionality
    DPAlgorithm algorithm = DPAlgorithm(runtimePath.runtimeNodeVector.size());
    RuntimePath answerPath;
    algorithm.execute(readExcel.graph, runtimePath, configs, answerPath);
    answerPath.print("recovered path");

    //TODO: handle the recovered path and dump into gantry outputs


    return 0;
}

bool PathRestoration::extractNode(const ReadExcel & readExcel, std::string & index, std::string & transTime,
        std::vector<RuntimeNode> * runtimeNodeVector) {
    Node node = Node(index, std::string());
    std::vector<Node>::const_iterator iterator = std::find(readExcel.graph.nodeVector.begin(),
                                                     readExcel.graph.nodeVector.end(), node);
    if (iterator == readExcel.graph.nodeVector.end()) {
        return false;
    }
    RuntimeNode runtimeNode = RuntimeNode(*iterator, transTime);
    runtimeNodeVector->push_back(runtimeNode);
    return true;
}


