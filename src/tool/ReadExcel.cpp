//
// Created by lida on 2020/3/31.
//

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "ReadExcel.h"

ReadExcel::ReadExcel() {
    graph = Graph();
}

Graph & ReadExcel::buildGraph(const std::string & csvDir) {
    //build graph from 3 csv files
    //edge.csv, mutual.csv, and mileage.csv
    readFromCSVFile(csvDir, "edge.csv", 1);
    readFromCSVFile(csvDir, "mutual.csv", 2);
    readFromCSVFile(csvDir, "mileage.csv", 3);

    std::cout << "nodes in graph = " << graph.nodeVector.size() << std::endl;
    graph.buildAllShortestPath();
    return graph;
}

void ReadExcel::readFromCSVFile(const std::string &dir, const std::string &fileName, int flag) {
    std::ifstream inputFileStream;
    std::string line;

    //FIXME: file separator is incompatible with Windows
    inputFileStream.open(dir + "/" + fileName);

    while(!inputFileStream.eof()){
        inputFileStream >> line;
        addEdgeFromLine(line, flag);
    }
}

void ReadExcel::addEdgeFromLine(const std::string& lineStr, int flag) {

    std::stringstream ss(lineStr);
    std::vector<std::string> vector;
    while (ss.good()) {
        std::string subStr;
        getline(ss, subStr, ',');
        std::cout << subStr << std::endl;
        vector.push_back(subStr);
    }

    Node startNode, endNode;
    extractNode(vector, 0, startNode);
    if (flag != 3)
        extractNode(vector, 3, endNode);

    if (flag == 1) {
        Edge edge = Edge(startNode, endNode);
        graph.edgeVector.push_back(edge);
    }
    else if (flag == 2) {
        startNode.mutualNodePtr = &endNode;
        endNode.  mutualNodePtr = &startNode;
    }
    else if (flag == 3) {
        startNode.mileage = atoi(vector[3].c_str());
    }
}

void ReadExcel::extractNode(const std::vector<std::string> &vector, int base, Node &node) {
    node = Node(vector[base+0], vector[base+1]);
    switch (vector[base+2].at(0)) {
        case '0':
            node.type = NORMALPORTAL;
            break;
        case '1':
            node.type = PROVINCIALPORTAL;
            break;
        case '3':
            node.type = TOLLSTATION;
            break;
    }

    std::vector<Node>::iterator iterator = std::find(graph.nodeVector.begin(), graph.nodeVector.end(), node);
    if (iterator != graph.nodeVector.end())
        node =  *iterator;
    else
        graph.nodeVector.push_back(node);
}


