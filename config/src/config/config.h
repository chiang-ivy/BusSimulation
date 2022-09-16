//
// Created by chian on 2021-05-30.
//

#ifndef BUSSIM_CONFIG_H
#define BUSSIM_CONFIG_H

#include <ctime>
#include "rapidjson/filereadstream.h"
#include "bus_system.h"

using namespace rapidjson;

class Config {
public:
    Config();
    ~Config();
    int processConfigJson();

    static BusLine* parseBusLineFromJson(Document& jsonDoc, char line);

    static time_t convertStrToTime(const char* timeString); //HH:MM:SS
    static char*  convertTimeToStr(const time_t timeData);

    static time_t addSeconds(time_t tt, int seconds);
    static time_t addMinutes(time_t tt, int minutes);

    static char* convertIntToStr(const int value);
};

#endif //BUSSIM_CONFIG_H
