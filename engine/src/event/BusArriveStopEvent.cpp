//
// Created by chian on 2021-06-15.
//

#include "BusArriveStopEvent.h"

BusArriveStopEvent::BusArriveStopEvent(time_t eventTime, char line, Bus* busPtr, Node<BusStop>* busStopNodePtr): BaseEvent(eventTime) {

    this->eventType = BusArriveStop;
    this->line = line;
    this->busPtr = busPtr;
    this->busStopNodePtr = busStopNodePtr;

}

BusArriveStopEvent::~BusArriveStopEvent() {

}

enum BaseEvent::EventType BusArriveStopEvent::getEventType() {
    return this->eventType;
}

std::string BusArriveStopEvent::printDetails() {
    static std::string message;

    message = "Event Type: BusArriveStopEvent | Event Time: ";
    message += Config::convertTimeToStr(getEventTime());
    message += " Bus Stop: ";
    message += this->busStopNodePtr->getContainPtr()->getBusStopName();
    message += " bus direction: ";
    message += this->busDirectionString();
    message += " bus id: ";
    message += Config::convertIntToStr(this->getBusPtr()->getBusID());

    return message;
}

std::string BusArriveStopEvent::busDirectionString() {

    static std::string bus_direction;

    switch (this->busPtr->getDirection()) {
        case Bus_Direction::forward:
            bus_direction = "forward";
            break;
        case Bus_Direction::backward:
            bus_direction = "backward";
            break;
    }

    return bus_direction;

}