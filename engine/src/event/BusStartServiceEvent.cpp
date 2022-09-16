//
// Created by chian on 2021-06-02.
//

#include <config/config.h>
#include "object/Bus.h"
#include "BusStartServiceEvent.h"

BusStartServiceEvent::BusStartServiceEvent(time_t eventTime, char line) : BaseEvent(eventTime){
    this->eventType = BusStartService;
    this->line = line;
    this->busPtr = new Bus(Bus_Direction::forward);
}

BusStartServiceEvent::~BusStartServiceEvent() = default;

enum BaseEvent::EventType BusStartServiceEvent::getEventType() {
    return this->eventType;
}

std::string BusStartServiceEvent::printDetails() {

    std::string message;

    message = "Event Type: BusStartService | Event Time: ";
    message += Config::convertTimeToStr(getEventTime());
    message += " bus id: ";
    message += Config::convertIntToStr(this->getBusPtr()->getBusID());

    return message;
}