//
// Created by chian on 2021-06-16.
//

#ifndef BUSSIM_BUSLEAVESTOPEVENT_H
#define BUSSIM_BUSLEAVESTOPEVENT_H

#include "BusArriveStopEvent.h"

class BusLeaveStopEvent: public BusArriveStopEvent {
public:

    BusLeaveStopEvent(time_t eventTime, char line, Bus* busPtr, Node<BusStop>* busStopNodePtr);
    ~BusLeaveStopEvent();

    std::string printDetails();

};

#endif //BUSSIM_BUSLEAVESTOPEVENT_H
