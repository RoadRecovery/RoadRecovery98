//
// Created by lida on 2020/3/31.
//

#ifndef ROADRECOVERY98_DPALGORITHM_H
#define ROADRECOVERY98_DPALGORITHM_H

#include "Algorithm.h"

class DPAlgorithm : public Algorithm {

public:

  virtual RuntimePath & execute(Graph & graph, RuntimePath & runtimePath, std::vector<double> & configs);
};


#endif //ROADRECOVERY98_DPALGORITHM_H
