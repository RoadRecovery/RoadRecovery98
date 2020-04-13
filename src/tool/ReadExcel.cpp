//
// Created by lida on 2020/3/31.
//

#include "ReadExcel.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>

ReadExcel::ReadExcel() {
    graph = Graph();
}

Graph & ReadExcel::buildGraph(const std::string & csvDir) {
    //build graph from 3 csv files
    //edge.csv, mutual.csv, and mileage.csv
    readFromCSVFile(csvDir, "edge.csv", 1);
    readFromCSVFile(csvDir, "mutual.csv", 2);

    //init
    for (int i = 0; i < graph.nodeVector.size(); i++)
      if (graph.nodeVector[i].type == TOLLSTATION)
        graph.nodeVector[i].mileage = 0;
    readFromCSVFile(csvDir, "mileage.csv", 3);

    std::cout << "nodes in graph = " << graph.nodeVector.size() << std::endl;
    std::cout << "edges in graph = " << graph.edgeVector.size() << std::endl;
    graph.buildAllShortestPath();
    graph.getShortestPath(Node("3D200B", ""), Node("G0035370030010", ""));
    return graph;
}

void ReadExcel::readFromCSVFile(const std::string &dir, const std::string &fileName, int flag) {
    std::ifstream inputFileStream;
    std::string line;

    //FIXME: file separator is incompatible with Windows
    inputFileStream.open(dir + "/" + fileName);

    bool firstLine = true;
    while(!inputFileStream.eof()){
        inputFileStream >> line;
        if (firstLine) {
            firstLine = false;
        }
        else {
            addEdgeFromLine(line, flag);
        }
    }
}

void ReadExcel::addEdgeFromLine(const std::string& lineStr, int flag) {

    std::stringstream ss(lineStr);
    std::vector<std::string> vector;

//    std::cout << lineStr << std::endl;
    while (ss.good()) {
        std::string subStr;
        getline(ss, subStr, ',');
        vector.push_back(subStr);
    }

    Node startNode, endNode;
    int startIndex = extractNode(vector, 0, startNode), endIndex;

    if (flag == 1) {
        endIndex = extractNode(vector, 3, endNode);
        graph.edgeVector.push_back(Edge(startNode, endNode));
    }
    else if (flag == 2) {
        endIndex = extractNode(vector, 3, endNode);
        if (startIndex >= 0 && endIndex >= 0) {
            graph.nodeVector[startIndex].mutualNodePtr = & graph.nodeVector[endIndex];
            graph.nodeVector[endIndex].mutualNodePtr = & graph.nodeVector[startIndex];
        }
    }
    else if (flag == 3) {
      if (startIndex >= 0) {
        graph.nodeVector[startIndex].mileage = atol(vector[2].c_str());
//        std::cout << graph.nodeVector[startIndex].index << ":" << graph.nodeVector[startIndex].mileage << std::endl;
      }
    }
}

/**
 * @return if find a node in graph, then return true; else return false.
 */
int ReadExcel::extractNode(const std::vector<std::string> &vector, int base, Node &node) {
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
    if (iterator != graph.nodeVector.end()) {
        node = *iterator;
        return std::distance(graph.nodeVector.begin(), std::find(graph.nodeVector.begin(), graph.nodeVector.end(), node));
    }
    else {
        graph.nodeVector.push_back(node);
        return -1;
    }
}




