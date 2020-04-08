//
// Created by lida on 2020/3/31.
//

#include <iostream>
#include "RuntimePath.h"

RuntimePath::RuntimePath() {}

RuntimePath::RuntimePath(Path& path, RuntimeNode & startRuntimeNode, RuntimeNode & endRuntimeNode)
:runtimeNodeVector(std::vector<RuntimeNode>()) {
  for (int i = 0; i < path.nodeVector->size(); ++i) {
    Node & node = path.nodeVector->at(i);
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

void RuntimePath::print(std::string desc) {
	std::cout << "---" << desc << " begin---" << std::endl;
	std::cout << "---length = " << runtimeNodeVector.size() << " ---" << std::endl;
//	for (RuntimeNode runtimeNode : runtimeNodeVector) {
//		System.out.println(fixedLengthString(runtimeNode.node.index, 20) + " " +
//			fixedLengthString(runtimeNode.node.source.toString(), 20)+ " " +
//			fixedLengthString(runtimeNode.transTime, 20) + " " +
//			fixedLengthString(String.valueOf(runtimeNode.node.mileage), 20) + " " +
//			fixedLengthString(runtimeNode.node.name, 20));
//	}
	std::cout << "---path end---" << std::endl;
}

void RuntimePath::add(RuntimePath path2) {
	if (!runtimeNodeVector.empty() && !path2.runtimeNodeVector.empty()
		&& runtimeNodeVector.back() == path2.runtimeNodeVector.front()) {
		if (path2.runtimeNodeVector.front().node.source == IDENTIFY) {
			runtimeNodeVector.back().node.source = IDENTIFY;
		}
		runtimeNodeVector.insert(runtimeNodeVector.end(),
								 path2.runtimeNodeVector.begin() + 1,
								 path2.runtimeNodeVector.end());
	} else {
		runtimeNodeVector.insert(runtimeNodeVector.end(),
								 path2.runtimeNodeVector.begin(),
								 path2.runtimeNodeVector.end());
	}
}
