//
// Created by chian on 2021-06-07.
//

#include <string.h>
#include "BusStop.h"

BusStop::BusStop(char* busStopName) {

    this->busStopName = std::string(busStopName);

    int index = this->busStopName.find_last_of('_') + 1;
    this->stopId = std::stoi(this->busStopName.substr(index));

    forwardPassengersPtr = new LinkedList<Passenger>();
    backwardPassengersPtr = new LinkedList<Passenger>();
}

BusStop::~BusStop() {
    this->forwardPassengersPtr->clear();
    delete this->forwardPassengersPtr;
    this->backwardPassengersPtr->clear();
    delete this->backwardPassengersPtr;
}

std::string BusStop::getBusStopName() const {
    return busStopName;
}

void BusStop::addPassenger(Passenger* passengerPtr, Bus_Direction direction) {
    Node<Passenger>* nodePtr = new Node<Passenger>(passengerPtr);

    switch (direction) {
        case Bus_Direction::forward:
            this->getForwardPassengersPtr()->appendNodeAtTail(nodePtr);
            break;
        case Bus_Direction::backward:
            this->getBackwardPassengersPtr()->appendNodeAtTail(nodePtr);
            break;
    }
}

void BusStop::setBusStopName(const char *busStopName) {
    this->busStopName = std::string(busStopName);
}

void BusStop::setBusStopName(std::string busStopName) {
    this->busStopName = busStopName;
}

LinkedList<Passenger>* BusStop::getForwardPassengersPtr()  {
    return forwardPassengersPtr;
}

LinkedList<Passenger>* BusStop::getBackwardPassengersPtr() {
    return backwardPassengersPtr;
}
