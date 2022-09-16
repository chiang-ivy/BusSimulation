//
// Created by chian on 2021-06-15.
//

#ifndef BUSSIM_BUSARRIVESTOPEVENT_H
#define BUSSIM_BUSARRIVESTOPEVENT_H

#include "BaseEvent.h"
#include "object/Bus.h"
#include "object/BusStop.h"
#include "engine/node.h"

class BusArriveStopEvent: public BaseEvent {
public:

    BusArriveStopEvent(time_t eventTime, char line, Bus* busPtr, Node<BusStop>* busStopNodePtr);
    ~BusArriveStopEvent();

    enum BaseEvent::EventType getEventType();
    std::string printDetails();

    Node<BusStop>* getBusStopNodePtr() { return busStopNodePtr; }
    Bus* getBusPtr() { return busPtr; }
    char getLine() { return line; }

    std::string busDirectionString();

protected:

    Bus* busPtr;
    char line;
    Node<BusStop>* busStopNodePtr;
};

#endif //BUSSIM_BUSARRIVESTOPEVENT_H
