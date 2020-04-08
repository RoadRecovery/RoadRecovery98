//
// Created by lida on 2020/3/31.
//

#ifndef ROADRECOVERY98_READEXCEL_H
#define ROADRECOVERY98_READEXCEL_H


#include "../entity/Graph.h"

class ReadExcel {

public:

    Graph graph;

    ReadExcel();

    Graph & buildGraph(const std::string & csvDir);

    static void readFromCSVFile(const std::string &dir, const std::string &fileName, int i);

    static void addEdgeFromLine(std::string lineStr, int flag);
};


#endif //ROADRECOVERY98_READEXCEL_H
