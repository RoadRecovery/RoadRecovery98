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
    readFromCSVFile(csvDir, "mileage.csv", 3);

    std::cout << "nodes in graph = " << graph.nodeVector.size() << std::endl;
    std::cout << "edges in graph = " << graph.edgeVector.size() << std::endl;
    graph.buildAllShortestPath();
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
    bool contains = extractNode(vector, 0, startNode);

    if (flag == 1) {
        extractNode(vector, 3, endNode);
        graph.edgeVector.emplace_back(startNode, endNode);
    }
    else if (flag == 2) {
        bool contains2 = extractNode(vector, 3, endNode);
        if (contains && contains2) {
            startNode.mutualNodePtr = &endNode;
            endNode.mutualNodePtr = &startNode;
        }
    }
    else if (flag == 3) {
      if (contains) {
        startNode.mileage = atol(vector[2].c_str());
        std::cout << startNode.index << ":" << startNode.mileage << std::endl;
      }
    }
}

/**
 * @return if find a node in graph, then return true; else return false.
 */
bool ReadExcel::extractNode(const std::vector<std::string> &vector, int base, Node &node) {
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

    std::vector<Node>::const_iterator iterator = std::find(graph.nodeVector.begin(), graph.nodeVector.end(), node);
    if (iterator != graph.nodeVector.end()) {
        std::cout << std::distance(graph.nodeVector.begin(), std::find(graph.nodeVector.begin(), graph.nodeVector.end(), node)) << std::endl;
        node = *iterator;
        return true;
    }
    else {
        graph.nodeVector.push_back(node);
        return false;
    }
}




