//
// Created by chian on 2021-06-07.
//

#include <string>
#include "Bus.h"

Bus::Bus(Bus_Direction direction) {
    this->direction = direction;

    busID = Bus::generateId();

    passengersPtr = new LinkedList<Passenger>();
}

Bus::~Bus() {
    delete passengersPtr;
}

std::string Bus::printDetails() {

    std::string message = "Bus id: ";
    message += std::to_string(this->busID);
    message += " moving ";
    message += (this->direction == Bus_Direction::forward ? "forward" : "backward");

    return message;
}

Bus_Direction Bus::getDirection() const {
    return direction;
}

void Bus::setDirection(Bus_Direction direction) {
    Bus::direction = direction;
}

LinkedList<Passenger>* Bus::getPassengersPtr() {
    return passengersPtr;
}

