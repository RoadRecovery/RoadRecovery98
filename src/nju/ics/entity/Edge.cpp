//
// Created by lida on 2020/4/1.
//

#include "include/Edge.h"

//reference must not refer to an empty object!!!
bool operator==(Edge & lhs, Edge & rhs) {
  return lhs.inNode == rhs.inNode && lhs.outNode == rhs.outNode;
}