//
// Created by lida on 2020/4/15.
//

#include "../src/core/PathRestoration.h"
#include "gtest/gtest.h"
#include <fstream>
#include "nlohmann/json.hpp"

std::string inputPath = "../testcases/test-data-with-oracle-20200327.txt";

TEST(PathRestorationTestSuite, RegressionTest) {
  std::ifstream infile(inputPath);
  nlohmann::json json;

  int testCaseCnt = 0;
  while (infile >> json) {
    testCaseCnt++;
    std::cout << "Index = " << testCaseCnt << std::endl;

    auto enStationId = json["enStationId"].get<std::string>();
    auto enTime = json["enTime"].get<std::string>();
    auto exStationId = json["exStationId"].get<std::string>();
    auto exTime = json["exTime"].get<std::string>();

    auto edgePath = std::string("/home/lida/Desktop/RoadRecovery98/inputs/edge.csv");
    auto mutualPath = std::string("/home/lida/Desktop/RoadRecovery98/inputs/mutual.csv");
    auto mileagePath = std::string("/home/lida/Desktop/RoadRecovery98/inputs/mileage.csv");

    auto modifyCost = json["modifyCost"].get<double>();
    auto addCost = json["addCost"].get<double>();
    auto deleteCost = json["deleteCost"].get<double>();
    auto deleteCost2 = json["deleteCost2"].get<double>();
    auto deleteEndCost = json["deleteEndCost"].get<double>();

    auto gantryInputsMiddle = json["gantryIdList"].get<std::vector<nlohmann::json>>();
    std::vector<std::pair<std::string, std::string>> gantryInputs;
    for (auto & i : gantryInputsMiddle) {
      std::string gantryHex = i["gantryHex"].get<std::string>();
      std::string transTime = i["transTime"].get<std::string>();
      gantryInputs.emplace_back(gantryHex, transTime);
    }

    PathRestoration pathRestoration = PathRestoration(
        enStationId,enTime,exStationId,exTime,
        edgePath, mutualPath, mileagePath,
        modifyCost,addCost,deleteCost,deleteCost2,deleteEndCost,
        gantryInputs);

    std::vector<std::pair<std::string, std::string> > gantryOutputs;
    pathRestoration.pathRestorationMethod(gantryOutputs);

    std::string retResult;
    int count = 0;
    for (auto & pair : gantryOutputs) {
      if (count++ > 0) retResult.append("|");
      retResult.append(pair.first);
    }

    auto manualResult = json["manualResult"].get<std::string>();

//    std::cout << "ret: " << retResult << std::endl;
//    std::cout << "man: " << manualResult << std::endl;

    EXPECT_EQ(manualResult, retResult) << "testCase Index = " << testCaseCnt;
//    break;
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
