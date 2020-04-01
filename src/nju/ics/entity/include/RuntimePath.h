//
// Created by lida on 2020/3/31.
//

#ifndef ROADRECOVERY98_RUNTIMEPATH_H
#define ROADRECOVERY98_RUNTIMEPATH_H

#include "Path.h"
#include "RuntimeNode.h"
#include <vector>
class RuntimePath {

public:
  std::vector<RuntimeNode> runtimeNodeVector;

  RuntimePath();

  RuntimePath(Path &path, RuntimeNode &startRuntimeNode,
              RuntimeNode &endRuntimeNode);

  long getLength();

  //TODO: getLiteralPath()

  //TODO: print(string desc)

  //TODO: add(RuntimePath path2)

};


#endif //ROADRECOVERY98_RUNTIMEPATH_H
