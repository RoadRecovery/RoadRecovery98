//
// Created by lida on 2020/3/31.
//

#include "PathRestoration.h"

PathRestoration::PathRestoration(const std::string &enStationId, const std::string &exStationId,
                                 const std::string &enTime, const std::string &exTime,
                                 const std::string &basicDataPath,
                                 const std::list<std::string> & gantryIdList):
                                 enStationId(enStationId), exStationId(exStationId),
                                 enTime(enTime), exTime(exTime),
                                 basicDataPath(basicDataPath),
                                 gantryIdList(gantryIdList){
}

int PathRestoration::pathRestorationMethod(std::list<std::map<std::string, std::string> > &GantryListMap) {





    return 0;
}
