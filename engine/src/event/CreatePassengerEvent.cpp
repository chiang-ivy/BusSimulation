//
// Created by chian on 2021-06-19.
//

#include "CreatePassengerEvent.h"

CreatePassengerEvent::CreatePassengerEvent(time_t eventTime, Passenger* passengerPtr) : BaseEvent(eventTime) {
    this->eventType = CreatePassenger;
    this->passengerPtr = passengerPtr;
}

CreatePassengerEvent::~CreatePassengerEvent() {

}

enum BaseEvent::EventType CreatePassengerEvent::getEventType() {

    return this->eventType;
}

std::string CreatePassengerEvent::printDetails() {

    static std::string message;

    message = "Event Type: CreatePassengerEvent | Event Time: ";
    message += Config::convertTimeToStr(getEventTime());
    message += " Passenger: ";
    message += passengerPtr->printDetails();

    return message;
}

Passenger *CreatePassengerEvent::getPassengerPtr() const {
    return passengerPtr;
}
