//
// Created by lida on 2020/4/15.
//

#include "../src/core/PathRestoration.h"
#include "gtest/gtest.h"
#include <fstream>
#include "nlohmann/json.hpp"

std::string inputPath = "../inputs/test-data-with-oracle-20200327.txt";

TEST(PathRestorationTestSuite, RegressionTest) {
  //TODO: read 6000+ test cases from ...

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
