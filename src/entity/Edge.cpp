//
// Created by lida on 2020/4/1.
//

#include "Edge.h"

//reference must not refer to an empty object!!!
bool operator==(const Edge & lhs, const Edge & rhs) {
  return lhs.inNode == rhs.inNode && lhs.outNode == rhs.outNode;
}

Edge::Edge(Node & inNode, Node & outNode): inNode(inNode),outNode(outNode) {
}
