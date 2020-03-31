//
// Created by lida on 2020/3/31.
//

#ifndef ROADRECOVERY98_EDGE_H
#define ROADRECOVERY98_EDGE_H

#include "Node.h"
class Edge {
public:
  Node& inNode;
  Node& outNode;

  //define {equals in Java}
  friend bool operator==(Edge & lhs, Edge & rhs);
};

bool operator==(Edge & lhs, Edge & rhs) {
  return lhs.inNode == rhs.inNode && lhs.outNode == rhs.outNode;
}


#endif //ROADRECOVERY98_EDGE_H
