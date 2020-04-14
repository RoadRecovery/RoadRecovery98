//
// Created by lida on 2020/3/31.
//

#include "RuntimePath.h"
#include <iomanip>
#include <iostream>

RuntimePath::RuntimePath() {}

RuntimePath::RuntimePath(Path& path, RuntimeNode & startRuntimeNode, RuntimeNode & endRuntimeNode) {
  for (int i = 0; i < path.nodeVector->size(); ++i) {
    Node & node = path.nodeVector->at(i);
    std::string transTime = std::string();
    if (node == startRuntimeNode.node) transTime = startRuntimeNode.transTime;
    if (node == endRuntimeNode.node)   transTime = endRuntimeNode.transTime;
    RuntimeNode runtimeNode = RuntimeNode(node, transTime);
    this->runtimeNodeVector.push_back(runtimeNode);
  }
}

long RuntimePath::getLength() {
  long length = 0;
  for (int i = 1; i < runtimeNodeVector.size() - 1; ++i) {
    length += runtimeNodeVector.at(i).node.mileage;
  }
  return length;
}

void RuntimePath::print(const std::string& desc) {
  std::cout << std::endl << "--- " << desc << " begin ---" << std::endl;
  std::cout << "--- length = " << runtimeNodeVector.size() << " ---" << std::endl << std::endl;
  for (int i = 0; i < runtimeNodeVector.size(); ++i) {
    RuntimeNode & runtimeNode = runtimeNodeVector[i];
    runtimeNode.print();
  }

  std::cout << "--- path end ---" << std::endl << std::endl;
}

void RuntimePath::add(RuntimePath path2) {
  if (!runtimeNodeVector.empty() && !path2.runtimeNodeVector.empty()
    && runtimeNodeVector.back() == path2.runtimeNodeVector.front()) {

    if (path2.runtimeNodeVector.front().node.source == IDENTIFY) {
      runtimeNodeVector.back().node.source = IDENTIFY;
    }
    runtimeNodeVector.insert(runtimeNodeVector.end(),
        path2.runtimeNodeVector.begin() + 1, path2.runtimeNodeVector.end());
  } else {
    runtimeNodeVector.insert(runtimeNodeVector.end(),
        path2.runtimeNodeVector.begin(),
        path2.runtimeNodeVector.end());
  }
}

RuntimePath::RuntimePath(std::vector<RuntimeNode> & runtimeNodeVector) {
  this->runtimeNodeVector = runtimeNodeVector;
}
