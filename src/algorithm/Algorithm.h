//
// Created by lida on 2020/3/31.
//

#ifndef ROADRECOVERY98_ALGORITHM_H
#define ROADRECOVERY98_ALGORITHM_H

#include "../entity/Graph.h"
#include "../entity/RuntimePath.h"
class Algorithm {

public:

  virtual RuntimePath execute(Graph & graph, RuntimePath & runtimePath, std::vector<double> & configs) = 0;

};


#endif //ROADRECOVERY98_ALGORITHM_H
