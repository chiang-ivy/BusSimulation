//
// Created by chian on 2021-06-07.
//

#ifndef BUSSIM_BUS_H
#define BUSSIM_BUS_H

#include <string.h>
#include "Enums.h"
#include "BusStop.h"
#include "engine/node.h"

class Bus {
private:
    Bus_Direction direction;
    Node<BusStop>* busStopPtr;
    int busID;
    LinkedList<Passenger>* passengersPtr;

public:
    Bus(Bus_Direction direction);
    ~Bus();

    Bus_Direction getDirection() const;

    void setDirection(Bus_Direction direction);

    int getBusID() { return busID; }

    std::string printDetails();

    LinkedList<Passenger>* getPassengersPtr();

    static int generateId() {
        static int id = 1;

        return id++;
    }
};
#endif //BUSSIM_BUS_H
