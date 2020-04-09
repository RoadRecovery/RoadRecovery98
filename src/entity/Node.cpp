//
// Created by lida on 2020/4/1.
//

#include "Node.h"

Node::Node() {
    this->mutualNodePtr = NULL;
}

Node::Node(const std::string &index, const std::string &name) {
  this->index = index;
  this->name = name;
  this->mutualNodePtr = NULL;
}

bool operator==(const Node &lhs, const Node &rhs) { return lhs.index == rhs.index; }



