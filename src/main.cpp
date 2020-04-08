#include "entity/Node.h"
#include "tool/ReadExcel.h"
#include <iostream>

int main(int argc, char* argv[]) {

  Node node1 = Node("index1", "name1", TOLLSTATION, NULL);
  Node node2 = Node("index2", "name2", TOLLSTATION, &node1);
  Node node3 = node1;
  Node & node4 = node1;

  if (node1 == *node2.mutualNodePtr) {
    std::cout << "node1 == *node2.mutualNodePtr\n";
  }
  if (node3 == node1) {
    std::cout << "node1 == node3\n";
  }
  if (node4 == node2) {
    std::cout << "node2 == node4\n";
  }


//    ReadExcel readExcel = ReadExcel();
//    readExcel.buildGraph("/Users/lind/Desktop/RoadRecovery98/inputs");

    return 0;
}
