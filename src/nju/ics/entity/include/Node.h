//
// Created by lida on 2020/3/31.
//

#ifndef ROADRECOVERY98_NODE_H
#define ROADRECOVERY98_NODE_H

#include <string>
#include "NodeSource.h"
#include "NodeType.h"

class Node {

public:
  std::string index;
  std::string name;
  NodeType type;
  NodeSource source;
  Node* mutualNodePtr;
  long mileage;

  //constructor without arguments, DO I really need default constructor?

  //copy a node element except for source
  Node(const std::string& index, const std::string& name, NodeType type, Node*mutualNodePtr) {
    this->index = index;
    this->name = name;
    this->type = type;
    this->mutualNodePtr = mutualNodePtr;
  }

  //define equals function as that in Java, using operator==
  friend bool operator==(Node& lhs, Node& rhs);

  //TODO: define clone as that in Java ???
};

bool operator==(Node &lhs, Node &rhs) { return lhs.index == rhs.index; }


#endif //ROADRECOVERY98_NODE_H
