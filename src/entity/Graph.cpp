//
// Created by lida on 2020/3/31.
//

#include "Graph.h"
#include <algorithm>
#include <iostream>
#include <queue>

Graph::Graph() { upperBound = 0x3fffffff; }

Path Graph::getShortestPath(const Node& inNode, const Node& outNode) {
    //FIXME
    //Java version
//  //Dijkstra algorithm
//  int from = nodes.indexOf(inNode);
//  int to = nodes.indexOf(outNode);
//
//  if (dist[from][to] == Integer.MAX_VALUE / 2) {
//    return null;
//  }
//  Path path = new Path();
//  for (int x = to; x != -1; x = pre_node[from][x]) {
//    Node node = (Node) (nodes.get(x)).clone();
//    node.source = (x == to || x == from) ? IDENTIFY : ADD;
//    path.nodeList.add(node);
//  }
//  Collections.reverse(path.nodeList);
//  return path;

  //C++ version
  int from = std::distance(nodeVector.begin(), std::find(nodeVector.begin(), nodeVector.end(), inNode));
  int to = std::distance(nodeVector.begin(), std::find(nodeVector.begin(), nodeVector.end(), outNode));
  return NULL;
}


struct NodeDijkstra {
  long dis;
  int index, pre_node;
  NodeDijkstra(int i, long d, int p) : index(i), dis(d), pre_node(p) {}
  bool operator<(const NodeDijkstra &n) const { return dis > n.dis; }
};

void Graph::buildAllShortestPath() {

  for (int i = 0; i < nodeVector.size(); ++i) {
    edges.push_back(std::vector<int>());
    dist.push_back(std::vector<int>());
    pre_node.push_back(std::vector<int>());
    for (int j = 0; j < nodeVector.size(); ++j) {
      dist[i].push_back(upperBound);
      pre_node[i].push_back(-1);
    }
  }

  for (int i = 0; i < edgeVector.size(); ++i) {
    Edge edge = edgeVector[i];
    int x = std::distance(nodeVector.begin(),
                          std::find(nodeVector.begin(), nodeVector.end(), edge.inNode));
    int y = std::distance(nodeVector.begin(),
                          std::find(nodeVector.begin(), nodeVector.end(), edge.outNode));
    edges[x].push_back(y);
  }

  std::priority_queue<NodeDijkstra> q;
  for (int from = 0; from < nodeVector.size(); ++from) {
//    std::fill(dist[from].begin(), dist[from].end(), upperBound); // TODO: to -1
//    std::fill(pre_node[from].begin(), pre_node[from].end(), -1);
    while (!q.empty()) q.pop();
    q.push(NodeDijkstra(from, 0, -1));

    while (!q.empty()) {
      NodeDijkstra x = q.top();
      q.pop();
      if (dist[from][x.index] >= x.dis) {
        dist[from][x.index] = x.dis;
        pre_node[from][x.index] = x.pre_node;
        if (x.index != from && nodeVector[x.index].type == TOLLSTATION) continue;
        // 收费站不能再往下转移
        for (int i = 0; i < edges[x.index].size(); ++i) {
          int y = edges[x.index][i];
          long disy = x.dis + nodeVector[y].mileage;
          if (dist[from][y] > disy) {
            q.push(NodeDijkstra(y, dist[from][y] = disy, x.index));
          }
        }
      }
    }
  }
}

