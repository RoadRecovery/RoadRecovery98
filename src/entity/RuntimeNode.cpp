//
// Created by lida on 2020/3/31.
//

#include "RuntimeNode.h"
#include <iomanip>
#include <iostream>

RuntimeNode::RuntimeNode(const Node & node, const std::string& transTime)
:node(node), transTime(transTime) {
}

bool operator==(const RuntimeNode & lhs, const RuntimeNode & rhs) {
  return lhs.node == rhs.node;
}

void RuntimeNode::print() const {
  std::cout << std::setw(15) << node.index
            << std::setw(5) << node.source
            << std::setw(5) << node.type
            << std::setw(10) << node.mileage
            << " " << node.name
            << std::endl;
}

