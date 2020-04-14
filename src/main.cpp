#include "entity/Node.h"
#include "tool/ReadExcel.h"
#include "core/PathRestoration.h"

int main(int argc, char* argv[]) {

  std::string enStationId = "G0035370030040";
  std::string enTime = "2020-01-22 16:35:31";
  std::string exStationId = "G0035370030010";
  std::string exTime = "2020-01-22 17:20:09";
  std::string basicDataPath = "/home/lida/Desktop/RoadRecovery98/inputs";
  std::vector<std::pair<std::string, std::string> > gantryInputs = std::vector<std::pair<std::string, std::string> >();
  gantryInputs.push_back(std::make_pair("3D200B", "2020-01-22 16:50:00"));
  gantryInputs.push_back(std::make_pair("3C2003", "2020-01-22 17:00:00"));

  PathRestoration pathRestoration = PathRestoration(enStationId, enTime, exStationId, exTime,
      basicDataPath, 0.01, 0.1, 500, 2, 100000, gantryInputs);
  std::vector<std::pair<std::string, std::string> > gantryOutputs;
  pathRestoration.pathRestorationMethod(gantryOutputs);

  return 0;
}


