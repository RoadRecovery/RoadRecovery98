//
// Created by lida on 2020/3/31.
//

#include "NullAlgorithm.h"
RuntimePath NullAlgorithm::execute(Graph & graph, RuntimePath & runtimePath,
                                   std::vector<double> & configs) {
  //simply return the original path
  return runtimePath;
}
