//
// Created by chian on 2021-06-02.
//

#ifndef BUSSIM_BUSSTARTSERVICEEVENT_H
#define BUSSIM_BUSSTARTSERVICEEVENT_H

#include "BaseEvent.h"
#include "object/Bus.h"

class BusStartServiceEvent: public BaseEvent {
public:
    BusStartServiceEvent(time_t eventTime, char line);
    ~BusStartServiceEvent();

    enum BaseEvent::EventType getEventType();
    std::string printDetails();

    Bus* getBusPtr() { return busPtr; }
    char getBusLine() { return line; }

protected:
    Bus* busPtr;
    char line;
};

#endif //BUSSIM_BUSSTARTSERVICEEVENT_H
