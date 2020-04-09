//
// Created by lida on 2020/3/31.
//

#ifndef ROADRECOVERY98_NULLALGORITHM_H
#define ROADRECOVERY98_NULLALGORITHM_H

#include "../entity/Graph.h"
#include "../entity/RuntimePath.h"
class NullAlgorithm {

public:

  virtual RuntimePath execute(Graph & graph, RuntimePath & runtimePath, std::vector<double> & configs);
};


#endif //ROADRECOVERY98_NULLALGORITHM_H