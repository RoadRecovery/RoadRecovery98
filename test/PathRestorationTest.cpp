//
// Created by lida on 2020/4/15.
//

#include "../src/core/PathRestoration.h"
#include "gtest/gtest.h"
#include <fstream>
#include "nlohmann/json.hpp"

std::string inputPath = "../inputs/test-data-with-oracle-20200327.txt";

TEST(PathRestorationTestSuite, RegressionTest) {
  std::ifstream infile(inputPath);
  nlohmann::json json;

  int testCaseCnt = 0;
  while (infile >> json) {
    testCaseCnt++;

    auto enStationId = json["enStationId"].get<std::string>();
    auto enTime = json["enTime"].get<std::string>();
    auto exStationId = json["exStationId"].get<std::string>();
    auto exTime = json["exTime"].get<std::string>();
    auto basicDataPath = std::string("/home/lida/Desktop/RoadRecovery98/inputs");

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
        enStationId,enTime,exStationId,exTime,basicDataPath,
        modifyCost,addCost,deleteCost,deleteCost2,deleteEndCost,
        gantryInputs);

    std::vector<std::pair<std::string, std::string> > gantryOutputs;
    pathRestoration.pathRestorationMethod(gantryOutputs);

    break;
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
