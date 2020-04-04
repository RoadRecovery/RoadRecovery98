//
// Created by lida on 2020/3/31.
//

#ifndef ROADRECOVERY98_RUNTIMENODE_H
#define ROADRECOVERY98_RUNTIMENODE_H

#include "Node.h"
class RuntimeNode {

public:
  Node& node;
  std::string & transTime;

  RuntimeNode(Node &node, std::string &transTime);

  friend bool operator==(RuntimeNode & lhs, RuntimeNode & rhs);

  //TODO: clone?
};



#endif //ROADRECOVERY98_RUNTIMENODE_H
