//
// Created by lida on 2020/3/31.
//

#include "Path.h"

Path::Path(std::vector<Node> &nodeList) : nodeVector(nodeList) {}

long Path::getLength() {
  long length = 0;
  for (int i = 1; i < nodeVector.size() - 1; ++i) {
    length += nodeVector[i].mileage;
  }
  return length;
}