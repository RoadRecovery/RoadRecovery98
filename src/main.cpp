#include "entity/Node.h"
#include "tool/ReadExcel.h"
#include <iostream>

int main(int argc, char* argv[]) {

    ReadExcel readExcel = ReadExcel();
    readExcel.buildGraph("/Users/lind/Desktop/RoadRecovery98/inputs");
    std::cout << "done" << std::endl;
    return 0;
}
