//
// Created by chian on 2021-06-16.
//

#include "BusLeaveStopEvent.h"

BusLeaveStopEvent::BusLeaveStopEvent(time_t eventTime, char line, Bus* busPtr, Node<BusStop>* busStopNodePtr)
                  : BusArriveStopEvent(eventTime, line, busPtr, busStopNodePtr) {

    this->eventType = BusLeaveStop;

}

BusLeaveStopEvent::~BusLeaveStopEvent() {

}

std::string BusLeaveStopEvent::printDetails() {

    static std::string message;

    message = "Event Type: BusLeaveStopEvent | Event Time: ";
    message += Config::convertTimeToStr(getEventTime());
    message += " Bus Stop: ";
    message += this->busStopNodePtr->getContainPtr()->getBusStopName();
    message += " bus direction: ";
    message += this->busDirectionString();
    message += " bus id: ";
    message += Config::convertIntToStr(this->getBusPtr()->getBusID());
    message += " with passengers ";
    message += Config::convertIntToStr(this->getBusPtr()->getPassengersPtr()->getSize());

    return message;
}

