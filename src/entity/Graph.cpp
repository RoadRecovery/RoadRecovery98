//
// Created by lida on 2020/3/31.
//

#include <algorithm>
#include <queue>
#include "Graph.h"

Graph::Graph() {}


struct NodeDijkstra {
	int dis;
	int index, pre_node;
	NodeDijkstra(int i, int d, int p) : index(i), dis(d), pre_node(p) {}
	bool operator<(const NodeDijkstra &n) const { return dis > n.dis; }
};

Path Graph::getShortestPath(const Node&, const Node&) {
    //FIXME: I just return a nonsense path.
    std::vector<Node> * vector;
    vector->push_back(Node());
    return Path(vector);
}

void Graph::buildAllShortestPath() {

    //FIXME: I comment code in this function.
	static std::vector<std::vector<int> > edges(nodeVector.size());
	for (int i = 0; i < edgeVector.size(); ++i) {
		Edge edge = edgeVector[i];
		int x = std::distance(nodeVector.begin(),
		        std::find(nodeVector.begin(), nodeVector.end(), edge.inNode));
		int y = std::distance(nodeVector.begin(),
		        std::find(nodeVector.begin(), nodeVector.end(), edge.outNode));
		edges[x].push_back(y);
	}

	static std::vector<std::vector<int> > dist(nodeVector.size(),
	        std::vector<int>(nodeVector.size()));
	static std::vector<std::vector<int> > pre_node(nodeVector.size(),
	        std::vector<int>(nodeVector.size()));
	std::priority_queue<NodeDijkstra> q;
	for (int from = 0; from < nodeVector.size(); ++from) {
		std::fill(dist[from].begin(), dist[from].end(), 0x3fffffff); // TODO: to -1
		std::fill(pre_node[from].begin(), pre_node[from].end(), -1);
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
					int disy = x.dis + nodeVector[y].mileage;
					if (dist[from][y] > disy) {
						q.push(NodeDijkstra(y, dist[from][y] = disy, x.index));
					}
				}
			}
		}
	}
}
