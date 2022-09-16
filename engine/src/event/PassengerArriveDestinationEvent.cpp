//
// Created by chian on 2021-06-20.
//

#include "PassengerArriveDestinationEvent.h"

PassengerArriveDestinationEvent::PassengerArriveDestinationEvent(time_t eventTime, Passenger* passengerPtr)
    : CreatePassengerEvent(eventTime, passengerPtr) {

    this->eventType = PassengerArriveDestination;

}

PassengerArriveDestinationEvent::~PassengerArriveDestinationEvent() {
    delete this->getPassengerPtr();
}

std::string PassengerArriveDestinationEvent::printDetails() {

    static std::string message;

    message = "Event Type: PassengerArriveDestinationEvent | Event Time: ";
    message += Config::convertTimeToStr(getEventTime());
    message += " Passenger: ";
    message += this->getPassengerPtr()->printDetails();
    message += " has arrived the destination: ";
    message += this->getPassengerPtr()->getDestinationPtr()->printDetails();

    return message;

}