//
// Created by chian on 2021-05-30.
//
#include "config.h"
#include <iostream>
#include <cstdio>
#include "bus_system.h"

Config::Config() {}

Config::~Config() {}

int Config::processConfigJson() {
    std::cout << "Read the config json file and save the values to class static members." << std::endl;

    FILE* fp = fopen("../config/config.json", "rb"); // non-Windows use "r"

    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    Document jsonConfigDoc;
    jsonConfigDoc.ParseStream(is);

    const char* startTimeStr = jsonConfigDoc["system"]["schedule"]["start_time"].GetString();
    const char* endTimeStr = jsonConfigDoc["system"]["schedule"]["end_time"].GetString();

    BusSystem::getBusSystem()->setStartTime(convertStrToTime(startTimeStr));
    BusSystem::getBusSystem()->setEndTime(convertStrToTime(endTimeStr));

    char linePrix[] = {'a', 'b', 'c'};

    for (int i=0; i < 3; i++) {

        BusLine* plPtr = parseBusLineFromJson(jsonConfigDoc, linePrix[i]);

        //plPtr->printDetails();

        (*BusSystem::getBusSystem()->getBusLinesMapPtr())[linePrix[i]] = plPtr;
        //std::cout << "Size " << BusSystem::getBusSystem()->getBusLinesMapPtr()->size() << std::endl;

        // Test code to print out the details of Bus Line
        // (*BusSystem::getBusSystem()->getBusLinesMapPtr())[linePrix[i]]->printDetails();
    }

    return 0;
}

BusLine* Config::parseBusLineFromJson(Document& jsonDoc, char line) {

    char* lineName = new char[7];
    sprintf(lineName,"line_%c", line);

    assert(jsonDoc.HasMember(lineName));

    assert(jsonDoc[lineName].HasMember("stop"));
    int numOfStops = jsonDoc[lineName]["stop"].GetInt();

    BusLine* busLinePtr = new BusLine(lineName, numOfStops);

    assert(jsonDoc[lineName].HasMember("bus_interval"));

    busLinePtr->setBusInterval(jsonDoc[lineName]["bus_interval"].GetInt());

    assert(jsonDoc[lineName].HasMember("intervals"));

    const Value& intervalArray =  jsonDoc[lineName]["intervals"];
    busLinePtr->setIntervals(intervalArray);

    return busLinePtr;
}

time_t Config::convertStrToTime(const char *timeString) { //HH:MM:SS

    const char *time_details = timeString;
    struct tm tm;
    memset(&tm, 0, sizeof(tm));
    strptime(time_details, "%H:%M:%S", &tm);

    tm.tm_hour = tm.tm_hour;
    tm.tm_year = 1900;
    tm.tm_mon = 0;
    tm.tm_mday = 1;

    time_t t = mktime(&tm);  // t is now your desired time_t

    return t;
}

char* Config::convertTimeToStr(const time_t timeData) {

    static char buffer[10];

    std::tm * ptm = std::localtime(&timeData);

    std::strftime(buffer, 10, "%H:%M:%S", ptm);

    return buffer;
}

time_t Config::addSeconds(time_t tt, int seconds) {

    tt += seconds;

    return tt;
}

time_t Config::addMinutes(time_t tt, int minutes) {

    tt += minutes * 60;

    return tt;
}

char* Config::convertIntToStr(const int value) {
    static char buffer[10];

    sprintf(buffer,"%d", value);

    return buffer;
}