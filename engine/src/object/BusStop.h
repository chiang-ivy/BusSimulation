//
// Created by chian on 2021-06-07.
//

#ifndef BUSSIM_BUSSTOP_H
#define BUSSIM_BUSSTOP_H

#include "Enums.h"
#include "engine/node.h"
#include "engine/linkedList.h"
#include "Passenger.h"

class BusStop {
protected:
    std::string busStopName;
    int         stopId;
    LinkedList<Passenger>* forwardPassengersPtr;
    LinkedList<Passenger>* backwardPassengersPtr;

public:
    BusStop(char* busStopName);
    ~BusStop();

    std::string getBusStopName() const;
    int getStopId() const { return stopId; }

    void setBusStopName(const char *busStopName);
    void setBusStopName(std::string busStopName);

    static Node<BusStop>* createNode(char* busStopName) {
        return new Node<BusStop>(new BusStop(busStopName));
    }

    void addPassenger(Passenger* passenger, Bus_Direction direction);

    void printDetail() {
        std::cout << "Bus Shop : " << busStopName << std::endl;
    }

    LinkedList<Passenger>* getForwardPassengersPtr();

    LinkedList<Passenger>* getBackwardPassengersPtr();

};
#endif //BUSSIM_BUSSTOP_H
