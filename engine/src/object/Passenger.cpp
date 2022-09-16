//
// Created by chian on 2021-06-19.
//

#include "Passenger.h"

#include "config/bus_system.h"
#include "config/config.h"
#include <ctime>

Location::Location(char line, int busStop) {
    this->line = line;
    this->busStop = busStop;
}

Location::~Location() = default;

char Location::getLine() const {
    return line;
}

void Location::setLine(char line) {
    Location::line = line;
}

int Location::getBusStop() const {
    return busStop;
}

void Location::setBusStop(int busStop) {
    Location::busStop = busStop;
}

std::string Location::printDetails() {

    static std::string message;

    message = "Line: ";
    message += this->line;
    message += " BusStop: ";
    message += Config::convertIntToStr(this->busStop);

    return message;
}

Passenger::Passenger() {

    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    /* initialize random seed: */
    //srand (time(NULL));
    srand((time_t)ts.tv_nsec); // fast-seeded

    this->id = this->generateId();

    this->beginPtr = this->randomLocation();

    this->destinationPtr = this->randomLocationExclude(this->beginPtr->getBusStop());
}

Passenger::~Passenger() {
    delete this->beginPtr;
    delete this->destinationPtr;
}


std::string Passenger::printDetails() {

    static std::string message;

    message = "Passenger ID: ";
    message += Config::convertIntToStr(this->id);
    message += " [Original] ";
    message += this->beginPtr->printDetails();
    message += " [Destination] ";
    message += this->destinationPtr->printDetails();

    return message;
}

Location* Passenger::randomLocation() {

    // Currently this function only consider Line A. It should extend to Line B and C.
    BusSystem* busSystem = BusSystem::getBusSystem();

    int numOfStop = (*busSystem->getBusLinesMapPtr())['a']->getNumStops();

    int randomStop = (rand() % numOfStop) + 1;

    return new Location('a', randomStop);
}

Location* Passenger::randomLocationExclude(int excludeStop) {

    // Currently this function only consider Line A. It should extend to Line B and C.
    BusSystem* busSystem = BusSystem::getBusSystem();

    int numOfStop = (*busSystem->getBusLinesMapPtr())['a']->getNumStops();

    int randomStop = (rand() % numOfStop) + 1;

    if (excludeStop == randomStop)
        randomStop = ((randomStop + 1) % numOfStop) + 1;

    return new Location('a', randomStop);
}

Location *Passenger::getBeginPtr() const {
    return beginPtr;
}

Location *Passenger::getDestinationPtr() const {
    return destinationPtr;
}
