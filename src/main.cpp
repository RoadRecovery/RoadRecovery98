#include "entity/Node.h"
#include "tool/ReadExcel.h"
#include "core/PathRestoration.h"
#include <iostream>

int main(int argc, char* argv[]) {

    //{"enTime":"2020-01-22 16:35:31","exTime":"2020-01-22 17:20:09",
    // "enStationId":"G0035370030040","exStationId":"G0035370030010",
    // "gantryIdList":[
    // {"transTime":"","gantryHex":"3D200B"},
    // {"transTime":"","gantryHex":"3C2003"}
    // ],"basicDataPath":"F:\\basic-data.xls",
    // "modifyCost":0.01,"addCost":0.1,"deleteCost":500,"deleteCost2":2,"deleteEndCost":100000,"manualResult":"G0035370030040|3C2019|3D200B|3D200C|3D200D|3D200E|3D2015|3D2010|G0035370030010"}
    //manually craft a test case
    std::string enStationId = "G0035370030040";
    std::string enTime = "2020-01-22 16:35:31";
    std::string exStationId = "G0035370030010";
    std::string exTime = "2020-01-22 17:20:09";
    std::string basicDataPath = "/Users/lind/Desktop/RoadRecovery98/inputs";
    std::vector<std::pair<std::string, std::string> > gantryInputs = std::vector<std::pair<std::string, std::string> >();
    gantryInputs.push_back(std::make_pair("3D200B", "2020-01-22 16:50:00"));
    gantryInputs.push_back(std::make_pair("3C2003", "2020-01-22 17:00:00"));


    PathRestoration pathRestoration = PathRestoration(enStationId, exStationId, enTime, exTime, basicDataPath,
            0.1, 500, 2, 0.01, 100000,
            gantryInputs);
    std::cout << "done" << std::endl;
    return 0;
}
