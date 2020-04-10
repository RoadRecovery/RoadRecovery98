//
// Created by lida on 2020/3/31.
//

#include "RuntimeNode.h"
#include <iostream>

RuntimeNode::RuntimeNode(const Node & node, const std::string& transTime)
:node(node), transTime(transTime) {
}

bool operator==(const RuntimeNode & lhs, const RuntimeNode & rhs) {
  return lhs.node == rhs.node;
}

void RuntimeNode::print() const {
    std::cout << node.index <<"    "<< node.name <<"    "<< node.type <<"    "<< transTime  << std::endl;
}

