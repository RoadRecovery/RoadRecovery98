//
// Created by lida on 2020/3/31.
//

#ifndef ROADRECOVERY98_RUNTIMENODE_H
#define ROADRECOVERY98_RUNTIMENODE_H

#include "Node.h"
class RuntimeNode {

public:
  Node node;
  std::string transTime;

  RuntimeNode(const Node & node, const std::string& transTime);

  void print() const;

  friend bool operator==(const RuntimeNode & lhs, const RuntimeNode & rhs);

  //TODO: clone?
};



#endif //ROADRECOVERY98_RUNTIMENODE_H
