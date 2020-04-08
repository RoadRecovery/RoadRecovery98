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
  Node();

  //copy a node element except for source
  Node(const std::string& index, const std::string& name, NodeType type, Node* mutualNodePtr);

  //define equals function as that in Java, using operator==
  friend bool operator==(const Node& lhs, const Node& rhs);

  //TODO: clone?
};



#endif //ROADRECOVERY98_NODE_H
