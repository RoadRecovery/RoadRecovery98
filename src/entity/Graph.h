//
// Created by lida on 2020/3/31.
//

#ifndef ROADRECOVERY98_GRAPH_H
#define ROADRECOVERY98_GRAPH_H

#include "Edge.h"
#include "Node.h"
#include "Path.h"
#include <vector>
class Graph {

public:

  std::vector<Node> nodeVector;
  std::vector<Edge> edgeVector;

  Graph();

  Path getShortestPath(const Node &, const Node &);

  //pre-process the shortest path in the graph
  void buildAllShortestPath();

};


#endif //ROADRECOVERY98_GRAPH_H
