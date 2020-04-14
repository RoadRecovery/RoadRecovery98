//
// Created by lida on 2020/4/1.
//

#include "Node.h"
#include <iomanip>
#include <iostream>

Node::Node() {
    this->mutualNodePtr = NULL;
}

Node::Node(const std::string &index, const std::string &name) {
  this->index = index;
  this->name = name;
  this->mutualNodePtr = NULL;
}

bool operator==(const Node &lhs, const Node &rhs) { return lhs.index == rhs.index; }

void Node::print() {
  std::cout << std::setw(20) << index
      << std::setw(20) << name
      << std::setw(20) << source
      << std::setw(20) << type
      << std::setw(20) << mileage;
}
Node::Node(const Node &node):
  index(node.index), name(node.name), type(node.type), mileage(node.mileage),
  source(node.source), mutualNodePtr(node.mutualNodePtr) {
}
