//
// Created by lida on 2020/3/31.
//

#include "include/RuntimeNode.h"

RuntimeNode::RuntimeNode(Node & node, std::string & transTime)
:node(node), transTime(transTime) {
}

bool operator==(RuntimeNode & lhs, RuntimeNode & rhs) {
  return lhs.node == rhs.node;
}

