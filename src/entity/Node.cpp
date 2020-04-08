//
// Created by lida on 2020/4/1.
//

#include "Node.h"

Node::Node(const std::string &index, const std::string &name, NodeType type,
           Node *mutualNodePtr) {
  this->index = index;
  this->name = name;
  this->type = type;
  this->mutualNodePtr = mutualNodePtr;
}

bool operator==(Node &lhs, Node &rhs) { return lhs.index == rhs.index; }

Node::Node() {
}


