//
// Created by chian on 2021-06-15.
//

#ifndef BUSSIM_BUSENDSERVICEEVENT_H
#define BUSSIM_BUSENDSERVICEEVENT_H

#include "BusStartServiceEvent.h"

class BusEndServiceEvent: public BaseEvent {
public:
    BusEndServiceEvent(time_t eventTime, char line, Bus* busPtr);
    ~BusEndServiceEvent();

    enum BaseEvent::EventType getEventType();
    std::string printDetails();

    Bus* getBusPtr() { return busPtr; }
    char getBusLine() { return line; }

protected:
    Bus* busPtr;
    char line;
};

#endif //BUSSIM_BUSENDSERVICEEVENT_H
