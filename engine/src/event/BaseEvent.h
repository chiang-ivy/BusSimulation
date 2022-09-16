//
// Created by chian on 2021-06-01.
//

#ifndef BUSSIM_BASEEVENT_H
#define BUSSIM_BASEEVENT_H

#include <ctime>
#include <config/config.h>
#include <string.h>

class BaseEvent {
protected:
    time_t eventTime;
public:
    BaseEvent(time_t eventTime) { this->eventTime = eventTime;}
    BaseEvent(const char* eventTime);
    ~BaseEvent();

    enum EventType {BusStartService, BusArriveStop, BusLeaveStop, BusEndService, CreatePassenger, PassengerArriveDestination};

    bool before(const BaseEvent& baseEvent) { return (this->getEventTime() <= baseEvent.getEventTime());}

    bool operator >= (const BaseEvent& baseEvent)  { return (this->getEventTime() >= baseEvent.getEventTime());}

    time_t getEventTime() const;

    virtual enum EventType getEventType() = 0;

    virtual std::string printDetails() = 0;

protected:
    enum EventType eventType;
};

#endif //BUSSIM_BASEEVENT_H
