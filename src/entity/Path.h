//
// Created by lida on 2020/3/31.
//

#ifndef ROADRECOVERY98_PATH_H
#define ROADRECOVERY98_PATH_H

#include "Node.h"
#include <vector>

class Path {

public:

  std::vector<Node> nodeVector;

  Path(std::vector<Node> nodeList);

  long getLength();

};


#endif //ROADRECOVERY98_PATH_H
