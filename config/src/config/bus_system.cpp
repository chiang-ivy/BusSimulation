//
// Created by chian on 2021-05-30.
//

#include <iostream>
#include "bus_system.h"

BusSystem* BusSystem::theInstance = NULL;

BusSystem::BusSystem() {

    //std::map<char, BusLine*> * busLinesMapPtr;

    busLinesMapPtr = new std::map<char, BusLine*>();
}

BusSystem::~BusSystem() {

    if (busLinesMapPtr != NULL) {
        for (std::map<char, BusLine*>::iterator itr = busLinesMapPtr->begin(); itr != busLinesMapPtr->end(); ++itr) {
            delete itr->second;
        }

        busLinesMapPtr->clear();

        delete busLinesMapPtr;
    }

}

BusSystem* BusSystem::getBusSystem() {
    if (BusSystem::theInstance == NULL) {
        BusSystem::theInstance = new BusSystem();
    }

    return BusSystem::theInstance;
}

void BusSystem::setStartTime(time_t startTime) {
    this->startTime = startTime;
}
time_t BusSystem::getStartTime() {
    return this->startTime;
}
void BusSystem::setEndTime(time_t endTime) {
    this->endTime = endTime;
}
time_t BusSystem::getEndTime() {
    return this->endTime;
}

BusLine::BusLine(char *line, int numStops) {

    this->line = line;
    this->numStops = numStops;
}

BusLine::~BusLine() {
    delete [] this->line;
    delete [] this->intervals;
}

void BusLine::setIntervals(const rapidjson::Value& intervalArray) {

    assert(intervalArray.IsArray());

    this->intervals = new double[intervalArray.Size()];

    for (SizeType i=0; i < intervalArray.Size(); i++) {
        this->intervals[i] = intervalArray[i].GetDouble();
    }

}

void BusLine::setBusInterval(int busInterval) {
    this->busInterval = busInterval;
}

int BusLine::getBusInterval() {
    return this->busInterval;
}

void BusLine::printDetails() {

    std::cout << "Bus line name: " << this->getLine() << std::endl;
    std::cout << "\t" << "bus intervals: " << this->getBusInterval() << std::endl;
    std::cout << "\t" << "stop number: " << this->getNumStops() << std::endl;
    std::cout << "\t" << "stop distance (bus run in minutes): "  << std::endl;

    for (int i=0; i < this->getNumStops() -1; i++) {
        std::cout << "\t\t" << (this->getIntervals())[i] << std::endl;
    }
}