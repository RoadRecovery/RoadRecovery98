//
// Created by lida on 2020/3/31.
//

#include "DPAlgorithm.h"
#include <iostream>

DPAlgorithm::DPAlgorithm(int size) {
  dpPath.clear();
  for (int i=0; i<size; i++) {
    dpPath.push_back(*new std::vector<RuntimePath>());
    for (int j = 0; j<2; j++) {
      dpPath[i].push_back(*new RuntimePath());
      dpPath[i][j].runtimeNodeVector = std::vector<RuntimeNode>();
    }
  }
}

void DPAlgorithm::execute(Graph &graph, RuntimePath &originalPath,
    std::vector<double> &configs, RuntimePath & answerPath) {

  //implement the DP core logic.
  double modifyCost = configs.at(0); //0.01
  double addCost = configs.at(1); //0.1
  double deleteCost = configs.at(2); //4000
  double deleteCost2 = configs.at(3); //2
  double deleteEndCost = configs.at(4); //1000000

  bool debug = true;

  int originalPathSize = originalPath.runtimeNodeVector.size();

  double dp[originalPathSize][2];
  double distanceFromDeletedNodesToIJ[originalPathSize][originalPathSize];

  double answer = -1;

  bool not_delete_first = originalPath.runtimeNodeVector.front().node.type == TOLLSTATION;
  bool not_delete_last = originalPath.runtimeNodeVector.back().node.type == TOLLSTATION;

  for (int i = 0; i < originalPathSize; ++i) {
    for (int j = i; j < originalPathSize; ++j) {
      distanceFromDeletedNodesToIJ[i][j] = j - i <= 1 ? 0 :
          distanceFromNodesToNodes(graph, originalPath.runtimeNodeVector, i, j);
      if (debug)
        std::cout <<"distance delete " <<  i << " " << j << ": " << distanceFromDeletedNodesToIJ[i][j] << std::endl;
    }
  }

  for (int i = 0; i < originalPathSize; ++i) {
    for (int flagI = 0; flagI <= 1; ++flagI) {
      // initial dp array
      dp[i][flagI] = (i == 0) ? (modifyCost * flagI) : -1;
      // nodeI: v_i or T(v_i) controlled by nodeI
      if (flagI && originalPath.runtimeNodeVector.at(i).node.mutualNodePtr == NULL) continue;
      RuntimeNode nodeI = originalPath.runtimeNodeVector.at(i);
      if (flagI) {
        nodeI.node = *(originalPath.runtimeNodeVector.at(i).node.mutualNodePtr);
        nodeI.transTime.clear();
      }

      dpPath[i][flagI].runtimeNodeVector.push_back(RuntimeNode(nodeI.node, nodeI.transTime));
      dpPath[i][flagI].runtimeNodeVector.front().node.source = IDENTIFY;
      for (int flagJ = 0; flagJ <= 1; ++flagJ) {
        for (int j = i - 1; j >= 0; --j) {
          // nodeJ: v_j or T(v_j) controlled by flagJ
          if (flagJ && originalPath.runtimeNodeVector.at(j).node.mutualNodePtr == NULL) continue;
          RuntimeNode nodeJ = originalPath.runtimeNodeVector.at(j);
          if (flagJ) {
            nodeJ.node = *(originalPath.runtimeNodeVector.at(j).node.mutualNodePtr);
            nodeJ.transTime.clear();
          }
          // shortest path from nodeJ to nodeI
          Path shortestPath = graph.getShortestPath(nodeJ.node, nodeI.node);
          if (shortestPath.nodeVector->empty()) continue;
          RuntimePath runtimeShortestPath = RuntimePath(shortestPath, nodeJ, nodeI);
          if (!(nodeI.node == nodeJ.node)
                          || (flagI == 1 && flagJ == 1)) { // When i == j and has one IDENTIFY, then IDENTIFY
            if (flagJ == 1) runtimeShortestPath.runtimeNodeVector.front().node.source = MODIFY;
            if (flagI == 1) runtimeShortestPath.runtimeNodeVector.back().node.source = MODIFY;
          }
          // FIXME: find suitable cost
          double distance = runtimeShortestPath.getLength();

          // update method 1: 从 (j, flagJ) 转移到 (i, flagI)，删除 j+1 到 i-1 之间的门架，补上 j 到 i 的最短路
          if (dp[j][flagJ] != -1) {
            double result = dp[j][flagJ]
                + modifyCost * flagI
                + deleteCost * (i - j - 1)
                + deleteCost2 * distanceFromDeletedNodesToIJ[j][i]
                + addCost * distance;

            // update
            if (dp[i][flagI] == -1 || result <= dp[i][flagI]) {
              dp[i][flagI] = result;
              dpPath[i][flagI].runtimeNodeVector.clear();
              dpPath[i][flagI].add(dpPath[j][flagJ]);
              dpPath[i][flagI].add(runtimeShortestPath);

              if (debug) {
                std::cout << "dp[" << i << "][" << flagI << "]: " << dp[i][flagI]
                  << " (from dp[" << j << "][" << flagJ << "])\n";
              }
            }
          }
          // update method 2: delete node 0 to j-1, j+1 to i-1
          if (!not_delete_first) {
            double result = modifyCost * (flagJ + flagI)
                + deleteEndCost * j
                + deleteCost * (i - j - 1)
                + deleteCost2 * distanceFromDeletedNodesToIJ[j][i]
                + addCost * distance;
            if (dp[i][flagI] == -1 || result <= dp[i][flagI]) {
              dp[i][flagI] = result;
              dpPath[i][flagI].runtimeNodeVector.clear();
              dpPath[i][flagI].add(runtimeShortestPath);

              if (debug) {
                std::cout << "dp[" << i << "][" << flagI << "]: " << dp[i][flagI]
                          << " (from dp[" << j << "][" << flagJ << "])\n";
              }
            }
          }
        }
      }

      if ((!not_delete_last || i == originalPathSize - 1)
          && (answer == -1 || dp[i][flagI] + (originalPathSize - 1 - i) * deleteEndCost < answer)
          && (dp[i][flagI] != -1)) {

        std::cout << "update answer" << std::endl;
        answer = dp[i][flagI] + (originalPathSize - 1 - i) * deleteEndCost; // 相当于后面都删掉
        answerPath = dpPath[i][flagI];
      }
    }
  }

}

double DPAlgorithm::distanceFromNodesToNodes(Graph &graph, std::vector<RuntimeNode> & nodeVector, int i, int j) {
  long ret = 0;
  RuntimeNode nodeI = nodeVector.at(i);
  RuntimeNode nodeJ = nodeVector.at(j);
  for (int k = i + 1; k < j; ++k) {
    long dis = -1;
    RuntimeNode nodeK = nodeVector.at(k);
    Path path = graph.getShortestPath(nodeI.node, nodeK.node);
    if (!path.nodeVector->empty()) dis = path.getLength();
    path = graph.getShortestPath(nodeK.node, nodeJ.node);
    if (!path.nodeVector->empty() && (dis == -1 || path.getLength() < dis)) dis = path.getLength();
    if (nodeK.node.mutualNodePtr != NULL) {
      nodeK.node = *nodeK.node.mutualNodePtr;
      nodeK.transTime.clear();
      path = graph.getShortestPath(nodeI.node, nodeK.node);
      if (!path.nodeVector->empty() && (dis == -1 || path.getLength() < dis)) dis = path.getLength();
      path = graph.getShortestPath(nodeK.node, nodeJ.node);
      if (!path.nodeVector->empty() && (dis == -1 || path.getLength() < dis)) dis = path.getLength();
    }
    ret += dis;
  }
  return ((double) ret) / (j - i - 1);
}

