//
// Created by chian on 2021-06-13.
//

#ifndef BUSSIM_SYSTEM_H
#define BUSSIM_SYSTEM_H

#include <config/bus_system.h>
#include "engine/linkedList.h"
#include "event/EventQueue.h"
#include "event/BusStartServiceEvent.h"
#include "event/BusEndServiceEvent.h"
#include "event/BusArriveStopEvent.h"
#include "event/BusLeaveStopEvent.h"
#include "event/CreatePassengerEvent.h"
#include "event/PassengerArriveDestinationEvent.h"
#include "BusStop.h"
#include "Passenger.h"

class System {

public:
    System();
    ~System();

    void createAllBusStopList();

    LinkedList<BusStop>* getBusStopList(char line) {
        return busStopListMap[line];
    }

    BusStop* getBusStop(char line, int stopId);

    void resetBusStopListMap();
    void printDetail();

    void setupStartQueue();

    EventQueue* getEventQueue() { return eventQueuePtr; }
    void setEventQueue(EventQueue* eventQueuePtr) { this->eventQueuePtr = eventQueuePtr; }

    void eventHandler(BaseEvent* eventPtr);

    void handleEvent(BusStartServiceEvent* eventPtr);
    void handleEvent(BusArriveStopEvent* eventPtr);
    void handleEvent(BusLeaveStopEvent* eventPtr);
    void handleEvent(BusEndServiceEvent* eventPtr);
    void handleEvent(CreatePassengerEvent* eventPtr);
    void handleEvent(PassengerArriveDestinationEvent* eventPtr);

private:
    static LinkedList<BusStop>* createBusStopList(char line, BusLine* busLineConfig);
    //void resetBusStopListMap();
    std::map<char,  LinkedList<BusStop>*> busStopListMap;
    bool isBusStopLineBuild;

    EventQueue* eventQueuePtr;

    void checkPassengersInBusOnBusStop(LinkedList<Passenger>* passengers, BusStop* busStopPtr, time_t time);
};

#endif //BUSSIM_SYSTEM_H
