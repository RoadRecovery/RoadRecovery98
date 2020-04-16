//
// Created by lida on 2020/3/31.
//

#ifndef ROADRECOVERY98_READEXCEL_H
#define ROADRECOVERY98_READEXCEL_H


#include "../entity/Graph.h"

class ReadExcel {

public:

    std::string csvDir;
    Graph graph;

    ReadExcel();

    Graph & buildGraph(const std::string &, const std::string &, const std::string &);

    void readFromCSVFile(const std::string &, int i);

    void addEdgeFromLine(const std::string& lineStr, int flag);

    int extractNode(const std::vector<std::string> &vector, int base, Node &node);


};


#endif //ROADRECOVERY98_READEXCEL_H
