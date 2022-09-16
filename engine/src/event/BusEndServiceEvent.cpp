//
// Created by chian on 2021-06-15.
//

#include "BusEndServiceEvent.h"

BusEndServiceEvent::BusEndServiceEvent(time_t eventTime, char line, Bus* busPtr): BaseEvent(eventTime) {
    this->eventType = BusEndService;
    this->line = line;
    this->busPtr = busPtr;
}

BusEndServiceEvent::~BusEndServiceEvent() {

}

enum BaseEvent::EventType BusEndServiceEvent::getEventType() {
    return this->eventType;
}

std::string BusEndServiceEvent::printDetails() {
    static std::string message;

    message = "Event Type: BusEndService | Event Time: ";
    message += Config::convertTimeToStr(getEventTime());
    message += " bus id: ";
    message += Config::convertIntToStr(this->getBusPtr()->getBusID());

    return message;
}