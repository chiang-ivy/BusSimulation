//
// Created by chian on 2021-05-30.
//

#ifndef BUSSIM_BUS_SYSTEM_H
#define BUSSIM_BUS_SYSTEM_H

#include <ctime>
#include <map>
#include "rapidjson/document.h"

using namespace rapidjson;

class BusLine {
private:
    char*     line;
    int       numStops;
    double*   intervals;
    int       busInterval;
public:
    BusLine(char* line, int numStops);
    ~BusLine();
    const char* getLine() { return this->line;}
    int getNumStops() { return this->numStops; }
    void setIntervals(const rapidjson::Value& intervalArray);
    double* getIntervals() {return intervals;}
    void setBusInterval(int busInterval);
    int getBusInterval();

    void printDetails();
};

class BusSystem {
private:
    time_t    startTime;
    time_t    endTime;
    std::map<char, BusLine*> * busLinesMapPtr;

    BusSystem();
public:
    ~BusSystem();
    static BusSystem* theInstance;
    static BusSystem* getBusSystem();
    void setStartTime(time_t startTime);
    time_t getStartTime();
    void setEndTime(time_t endTime);
    time_t getEndTime();
    std::map<char, BusLine*> * getBusLinesMapPtr() { return this->busLinesMapPtr; }

    double* getBusLineIntervals(char line) { return (*this->busLinesMapPtr)[line]->getIntervals(); }
};

#endif //BUSSIM_BUS_SYSTEM_H
