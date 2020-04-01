//
// Created by lida on 2020/3/31.
//

#include "include/RuntimePath.h"

RuntimePath::RuntimePath() {}

RuntimePath::RuntimePath(Path& path, RuntimeNode & startRuntimeNode, RuntimeNode & endRuntimeNode)
:runtimeNodeVector(std::vector<RuntimeNode>()) {
  for (int i = 0; i < path.nodeVector.size(); ++i) {
    Node & node = path.nodeVector[i];
    std::string transTime = std::string();
    if (node == startRuntimeNode.node) transTime = startRuntimeNode.transTime;
    if (node == endRuntimeNode.node)   transTime = endRuntimeNode.transTime;
    runtimeNodeVector.push_back(RuntimeNode(node, transTime));
  }
}

long RuntimePath::getLength() {
  long length = 0;
  for (int i = 1; i < runtimeNodeVector.size() - 1; ++i) {
    length += runtimeNodeVector[i].node.mileage;
  }
  return length;
}