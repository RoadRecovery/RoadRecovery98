//
// Created by lida on 2020/3/31.
//

#include "PathRestoration.h"
#include "../algorithm/DPAlgorithm.h"

PathRestoration::PathRestoration( std::string &enStationId,  std::string &exStationId,
                                  std::string &enTime,  std::string &exTime,
                                  std::string &basicDataPath,
                                  double addCost,double deleteCost,double deleteCost2,double modifyCost,
                                  double deleteEndCost,
                                 const std::vector<std::pair<std::string, std::string> > & gantryInputs):
        enStationId(enStationId), exStationId(exStationId),
        enTime(enTime), exTime(exTime),
        basicDataPath(basicDataPath),
        addCost(addCost), deleteCost(deleteCost), deleteCost2(deleteCost2), modifyCost(modifyCost),
        deleteEndCost(deleteEndCost),
        gantryInputs(gantryInputs){
}

int PathRestoration::pathRestorationMethod(std::vector<std::pair<std::string, std::string> > & gantryOutputs) {

    //TODO: construct data structure that algorithm needs
    ReadExcel readExcel = ReadExcel();
    readExcel.buildGraph(basicDataPath);

    std::vector<double> configs;
    configs.push_back(modifyCost);
    configs.push_back(addCost);
    configs.push_back(deleteCost);
    configs.push_back(deleteCost2);
    configs.push_back(deleteEndCost);

    std::vector<RuntimeNode> *runtimeNodeVector = new std::vector<RuntimeNode>();
    //start node
    if (!extractNode(readExcel, enStationId, enTime, runtimeNodeVector)) {
        //TODO: no entry node.
        return -1;
    }

    //middle gantry list
    std::vector<std::pair<std::string, std::string> >::const_iterator iter;
    for (iter = gantryInputs.begin(); iter != gantryInputs.end(); iter++) {
        std::string firstStr = iter->first;
        std::string secondStr = iter->second;
        if (!extractNode(readExcel, firstStr, secondStr, runtimeNodeVector)) {
            //TODO: no gantry node
            return -1;
        }
    }

    //end node
    if (!extractNode(readExcel, exStationId, exTime, runtimeNodeVector)) {
        //TODO: no exit node.
        return -1;
    }

    RuntimePath runtimePath = RuntimePath(runtimeNodeVector);

    //TODO: handle boundary cases


    //TODO: core functionality @Fancy
//    DPAlgorithm algorithm = DPAlgorithm();
//    RuntimePath retRuntimePath = algorithm.execute(readExcel.graph, runtimePath, configs);
    RuntimePath retRuntimePath = RuntimePath();

    //TODO: dump into gantry outputs
    for (std::vector<RuntimeNode>::const_iterator iter = retRuntimePath.runtimeNodeVector->begin();
            iter != retRuntimePath.runtimeNodeVector->end(); iter++) {
        iter->print();
    }

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
    RuntimeNode runtimeNode = RuntimeNode(node, transTime);
    runtimeNodeVector->push_back(runtimeNode);
    return true;
}

