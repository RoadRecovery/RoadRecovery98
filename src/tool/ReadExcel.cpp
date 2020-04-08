//
// Created by lida on 2020/3/31.
//

#include <iostream>
#include <fstream>
#include "ReadExcel.h"

ReadExcel::ReadExcel() {
    graph = Graph();
}

Graph & ReadExcel::buildGraph(const std::string & csvDir) {
    //TODO: build graph from 3 csv files
    //edge.csv, mutual.csv, and mileage.csv
    readFromCSVFile(csvDir, "edge.csv", 1);
//    readFromCSVFile(csvDir, "mutual.csv", 2);
//    readFromCSVFile(csvDir, "mileage.csv", 3);

    std::cout << "nodes in graph = " << graph.nodeVector.size() << std::endl;
    graph.buildAllShortestPath();
    return graph;
}

void ReadExcel::readFromCSVFile(const std::string &dir, const std::string &fileName, int flag) {
    std::ifstream inputFileStream;
    std::string line;
    //FIXME: incompatible with Windows
    inputFileStream.open(dir + "/" + fileName);

    bool firstLine = true;
    while(!inputFileStream.eof()){
        inputFileStream >> line;
        if (!firstLine) {
            addEdgeFromLine(line, flag);
        }
        else firstLine = false;
    }

}

void ReadExcel::addEdgeFromLine(std::string lineStr, int flag) {
    //TODO:
    std::cout << lineStr << std::endl;
}


