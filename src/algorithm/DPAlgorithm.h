//
// Created by lida on 2020/3/31.
//

#ifndef ROADRECOVERY98_DPALGORITHM_H
#define ROADRECOVERY98_DPALGORITHM_H

#include "Algorithm.h"

class DPAlgorithm : public Algorithm {

public:
  std::vector<std::vector<RuntimePath> > dpPath;

  DPAlgorithm(int size);

  virtual void execute(Graph & graph, RuntimePath & runtimePath, std::vector<double> & configs, RuntimePath &);

  double distanceFromNodesToNodes(Graph &graph, std::vector<RuntimeNode> & vector, int i, int j);
};



#endif //ROADRECOVERY98_DPALGORITHM_H
