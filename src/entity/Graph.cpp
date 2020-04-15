//
// Created by lida on 2020/3/31.
//

#include "Graph.h"
#include <algorithm>
#include <iostream>
#include <queue>

Graph::Graph() { upperBound = 0x3fffffff; built = false; }

Path Graph::getShortestPath(const Node& inNode, const Node& outNode) {

  int from = std::distance(nodeVector.begin(), std::find(nodeVector.begin(), nodeVector.end(), inNode));
  int to = std::distance(nodeVector.begin(), std::find(nodeVector.begin(), nodeVector.end(), outNode));

  std::vector<Node> nodes = std::vector<Node>();
  if (dist[from][to] == upperBound) return Path(nodes);

  for (int x = to; x != -1; x = pre_node[from][x]) {
  	Node node(nodeVector[x]);
  	node.source = (x == to || x == from) ? IDENTIFY : ADD;
  	nodes.push_back(node);
  }
  std::reverse(nodes.begin(), nodes.end());
  return Path(nodes);
}

struct NodeDijkstra {
  long dis;
  int index, pre_node;
  NodeDijkstra(int i, long d, int p) : index(i), dis(d), pre_node(p) {}
  bool operator<(const NodeDijkstra &n) const { return dis > n.dis; }
};

void Graph::buildAllShortestPath() {
  built = true;

//  std::cout << "build shortest path init." << std::endl;
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

//  std::cout << "build shortest path middle." << std::endl;
  std::priority_queue<NodeDijkstra> q;
  for (int from = 0; from < nodeVector.size(); ++from) {
//    std::cout << "update from " << from << std::endl;
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
//  std::cout << "build shortest path done." << std::endl;
}

