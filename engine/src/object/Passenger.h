//
// Created by chian on 2021-06-19.
//

#ifndef BUSSIM_PASSENGER_H
#define BUSSIM_PASSENGER_H

#include <string.h>
#include <iostream>

class Location {

private:

    char line;
    int  busStop;

public:

    Location(char line, int busStop);
    ~Location();

    char getLine() const;

    void setLine(char line);

    int getBusStop() const;

    void setBusStop(int busStop);

    std::string printDetails();

    bool match(Location* locPtr) {
        if (this->getLine() != locPtr->getLine()) {
            return false;
        }
        else if (this->getBusStop() != locPtr->getBusStop()){
            return false;
        }
        return true;
    }
};

class Passenger {

private:

    Location* beginPtr;
    Location* destinationPtr;
    int       id;

public:

    Passenger();
    ~Passenger();

    Location* randomLocation();
    Location* randomLocationExclude(int excludeStop);

    std::string printDetails();

    Location *getBeginPtr() const;

    Location *getDestinationPtr() const;

    static int generateId() {
        static int id = 1;

        return id++;
    }
};

#endif //BUSSIM_PASSENGER_H
