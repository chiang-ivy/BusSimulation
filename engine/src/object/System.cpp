//
// Created by chian on 2021-06-13.
//

#include "System.h"
#include <vector>

System::System() {

    this->isBusStopLineBuild = false;
    this->eventQueuePtr = new EventQueue();
}

System::~System() noexcept {
    delete this->eventQueuePtr;
}

void System::createAllBusStopList() {

    if (this->isBusStopLineBuild) {
        return;
    }

    if (this->busStopListMap.size() > 0) {
        this->resetBusStopListMap();
    }

    // LinkedList<BusStop>* listPtr = system.createBusStopList((*BusSystem::getBusSystem()->getBusLinesMapPtr())['a']);
    static const char lines[] = {'a', 'b', 'c'};

    for (int i=0; i < 3; i++) {
        this->busStopListMap[lines[i]] = this->createBusStopList(lines[i], (*BusSystem::getBusSystem()->getBusLinesMapPtr())[lines[i]]);
    }

    this->isBusStopLineBuild = true;
}
// This is not the good way to find the bus stop in system. I just want to keep it simple. Ivy, do you have ideal how to improve it.
BusStop* System::getBusStop(char line, int stopId) {

    if (this->busStopListMap.find(line) == this->busStopListMap.end()) { // Can't find bus line in map
        std::cerr << "Can't find bus line: " << line << " in System busStopMap. " << std::endl;
    }
    else {
        LinkedList<BusStop>* linkedListPtr = this->busStopListMap[line];
        Node<BusStop>* nodePtr = linkedListPtr->getHead();

        while (nodePtr != NULL) {
            if (nodePtr->getContainPtr()->getStopId() == stopId) {
                return nodePtr->getContainPtr();
            }

            nodePtr = nodePtr->getPostPtr();
        }
    }

    return NULL;
}

void System::resetBusStopListMap() {

    for (std::map<char, LinkedList<BusStop>*>::iterator it=busStopListMap.begin(); it!=busStopListMap.end(); ++it ) {
        it->second->clear();

        delete it->second;
    }

    busStopListMap.clear();
}

void System::printDetail() {

    for (std::map<char, LinkedList<BusStop>*>::iterator it=busStopListMap.begin(); it!=busStopListMap.end(); ++it ) {
        std::cout << "Line: " << it->first << std::endl;
        it->second->printDetail();
    }
}

LinkedList<BusStop>* System::createBusStopList(char line, BusLine* busLineConfig) {

    LinkedList<BusStop>* busStopListPtr = new LinkedList<BusStop>();

    if (busLineConfig == NULL)
        return busStopListPtr;

    int numOfStops = busLineConfig->getNumStops();

    for (int i=1; i <= numOfStops; i++) {

        static char busStopName[20];

        sprintf(busStopName,"line_%c_%02d", line, i);

        Node<BusStop>* nodePtr = BusStop::createNode(busStopName);

        busStopListPtr->appendNodeAtTail(nodePtr);
    }

    return busStopListPtr;
}

void System::setupStartQueue() {

    EventQueue* eventQ = this->getEventQueue();

    time_t startTime = BusSystem::getBusSystem()->getStartTime();
    time_t endTime   = BusSystem::getBusSystem()->getEndTime();

    int lineA_busInterval = (*(BusSystem::getBusSystem()->getBusLinesMapPtr()))['a']->getBusInterval();

    time_t currTime = startTime;

    eventQ->insertEvent(new CreatePassengerEvent(currTime, new Passenger()));

    int i = 0;

    while (currTime <= endTime) {
        BusStartServiceEvent* bsePtr = new BusStartServiceEvent(currTime, 'a');

        eventQ->insertEvent(bsePtr);

        currTime = Config::addMinutes(currTime, (*(BusSystem::getBusSystem()->getBusLinesMapPtr()))['a']->getBusInterval());

        //break;
        //i++;
        //if (i > 1)
        //    break; //Test code need to be removed. Nick Chiang
    }

}

// Objective: handle the event and free the input event;
void System::eventHandler(BaseEvent* eventPtr) {

    switch (eventPtr->getEventType()) {
        case BaseEvent::BusStartService:
            handleEvent((BusStartServiceEvent*)eventPtr);
            delete (BusStartServiceEvent*)eventPtr;
            break;
        case BaseEvent::BusArriveStop:
            handleEvent((BusArriveStopEvent*)eventPtr);
            delete (BusArriveStopEvent*)eventPtr;
            break;
        case BaseEvent::BusLeaveStop:
            handleEvent((BusLeaveStopEvent*)eventPtr);
            delete (BusLeaveStopEvent*)eventPtr;
            break;
        case BaseEvent::BusEndService:
            handleEvent((BusEndServiceEvent*)eventPtr);
            delete (BusEndServiceEvent*)eventPtr;
            break;
        case BaseEvent::CreatePassenger:
            handleEvent((CreatePassengerEvent*)eventPtr);
            delete (CreatePassengerEvent*)eventPtr;
            break;
        case BaseEvent::PassengerArriveDestination:
            handleEvent((PassengerArriveDestinationEvent*)eventPtr);
            delete (PassengerArriveDestinationEvent*)eventPtr;
            break;
    }
}

void System::handleEvent(BusStartServiceEvent* eventPtr) {

    std::cout << eventPtr->printDetails() << std::endl;

    EventQueue* eventQ = this->getEventQueue();
    char line = eventPtr->getBusLine();

    LinkedList<BusStop>* busStopListPtr = this->getBusStopList(line);
    Node<BusStop>* busStartNodePtr = busStopListPtr->getHead();

    Bus* busPtr = eventPtr->getBusPtr();
    BusArriveStopEvent* busArriveStopEventPtr = new BusArriveStopEvent(Config::addMinutes(eventPtr->getEventTime(), 2), line, busPtr, busStartNodePtr);

    eventQ->insertEvent(busArriveStopEventPtr);
}
void System::handleEvent(BusArriveStopEvent* eventPtr) {

    std::cout << eventPtr->printDetails() << std::endl;

    EventQueue* eventQ = this->getEventQueue();

    Node<BusStop>* busStopNodePtr = eventPtr->getBusStopNodePtr();
    Bus* busPtr = eventPtr->getBusPtr();

    char line = eventPtr->getLine();

    int delay = 3; // Set default wait time for 3 minutes. It should be dynamic based on number of passengers need to get on bus.

    // Check to see if there is any passenger need to get out of bus
    if (busPtr->getPassengersPtr()->getSize() > 0) { //
        checkPassengersInBusOnBusStop(busPtr->getPassengersPtr(), busStopNodePtr->getContainPtr(), eventPtr->getEventTime());
    }

    // Put passenger waiting in bus stop up to bus
    switch (busPtr->getDirection()) {
        case Bus_Direction::forward:
            busPtr->getPassengersPtr()->appendLinkedListAtTail(busStopNodePtr->getContainPtr()->getForwardPassengersPtr());
            break;
        case Bus_Direction::backward:
            busPtr->getPassengersPtr()->appendLinkedListAtTail(busStopNodePtr->getContainPtr()->getBackwardPassengersPtr());
            break;
    }


    BusLeaveStopEvent* busLeaveStopEvent = new BusLeaveStopEvent(Config::addMinutes(eventPtr->getEventTime(), delay),
                                                                 line, busPtr, eventPtr->getBusStopNodePtr());

    eventQ->insertEvent(busLeaveStopEvent);

}
void System::checkPassengersInBusOnBusStop(LinkedList<Passenger>* passengers, BusStop* busStopPtr, time_t time) {

    Node<Passenger>* passengerNodePtr = passengers->getHead();

    std::vector<Node<Passenger>*> removedPassengers;

    while (passengerNodePtr != NULL) {

        // Assume the passenger on bus is on same bus line. The codes need to be changed when consider cross bus line travel.
        if (passengerNodePtr->getContainPtr()->getDestinationPtr()->getBusStop() == busStopPtr->getStopId() ) {
            removedPassengers.push_back(passengerNodePtr);
        }

        passengerNodePtr = passengerNodePtr->getPostPtr();
    }

    for (Node<Passenger>* passengerNeedRemove : removedPassengers) {
        passengers->removeNode(passengerNeedRemove);
        time += 5; // Assume one person leave bus need 5 seconds
        PassengerArriveDestinationEvent* passengerArriveDestinationEventPtr = new PassengerArriveDestinationEvent(time, passengerNeedRemove->getContainPtr());

        this->getEventQueue()->insertEvent(passengerArriveDestinationEventPtr);

        passengerNeedRemove->setContainPtr(NULL);

        delete passengerNeedRemove;
    }
}

void System::handleEvent(BusLeaveStopEvent* eventPtr) {

    std::cout << eventPtr->printDetails() << std::endl;

    EventQueue* eventQ = this->getEventQueue();

    Node<BusStop>* busStartNodePtr = eventPtr->getBusStopNodePtr();
    Bus* busPtr = eventPtr->getBusPtr();

    char line = eventPtr->getLine();
    Node<BusStop>* nextBusStartNodePtr = NULL;
    int delay = 0;
    double* busIntervals = BusSystem::getBusSystem()->getBusLineIntervals(line);
    time_t nextEventTime = eventPtr->getEventTime();

    int id;
    switch (busPtr->getDirection()) {
        case Bus_Direction::forward:

            if (busStartNodePtr->getPostPtr() == NULL) { // The bus reaches the end of line it will turn around
                if (busPtr->getDirection() == Bus_Direction::forward) {
                    busPtr->setDirection(Bus_Direction::backward);
                    id = -2; // This is a special case for bus turn around
                    nextBusStartNodePtr = busStartNodePtr;
                }
                else {
                    //busPtr->setDirection(Bus_Direction::backward);
                    nextBusStartNodePtr = busStartNodePtr->getPrePtr();
                    id = busStartNodePtr->getContainPtr()->getStopId() - 2; // Ivy, do you know why I need to minus 2.
                }
            }
            else {
                nextBusStartNodePtr = busStartNodePtr->getPostPtr();
                id = busStartNodePtr->getContainPtr()->getStopId() - 1;
            }

            break;
        case Bus_Direction::backward:

            if (busStartNodePtr->getPrePtr() == NULL) { // The bus has turned around and move back the original bus stop.
                id = -1; // This is for special case which BusEndServiceEvent will be issued.
                delay = 60 * 2; // set default as two minuses
            }
            else {
                nextBusStartNodePtr = busStartNodePtr->getPrePtr();
                id = busStartNodePtr->getContainPtr()->getStopId() - 2; // Ivy, do you know why I need to minus 2.
            }

            break;
    }

    if (id != -1) {
        if (id == -2) {
            delay = 180; // delay 3 minutes when the bus turn around at the end of route
        }
        else {
            delay = (int) (60 * busIntervals[id]);
        }
        nextEventTime = nextEventTime + delay;

        BusArriveStopEvent* busArriveStopEventPtr = new BusArriveStopEvent(nextEventTime, line, busPtr, nextBusStartNodePtr);
        eventQ->insertEvent(busArriveStopEventPtr);
    }
    else {
        nextEventTime = nextEventTime + delay;

        BusEndServiceEvent* busEndServiceEventPtr = new BusEndServiceEvent(nextEventTime, line, busPtr);
        eventQ->insertEvent(busEndServiceEventPtr);
    }

}
void System::handleEvent(BusEndServiceEvent* eventPtr) {

    std::cout << eventPtr->printDetails() << std::endl;

    Bus* busPtr = eventPtr->getBusPtr();

    delete busPtr;
}

void System::handleEvent(CreatePassengerEvent* eventPtr) {

    std::cout << eventPtr->printDetails() << std::endl;

    // Implement dispatch passenger into bus stop

    Passenger* passengerPtr = eventPtr->getPassengerPtr();

    BusStop* targetStop = this->getBusStop('a', passengerPtr->getBeginPtr()->getBusStop()); // Currently only support Bus Line A

    if (passengerPtr->getBeginPtr()->getBusStop() < passengerPtr->getDestinationPtr()->getBusStop()) {
        // Passenger should take the forward bus
        targetStop->addPassenger(passengerPtr, Bus_Direction::forward);
    }
    else {
        // Passenger should take the backward bus
        targetStop->addPassenger(passengerPtr, Bus_Direction::backward);
    }

    // Create next CreatePassengerEvent (set default delay for 15 seconds)
    time_t deadLineToGeneratePassenger =  BusSystem::getBusSystem()->getEndTime() - 60*60; // Do not generate passenger within 60 minutes of Bus System ends

    if (eventPtr->getEventTime() + 15 < deadLineToGeneratePassenger) {
        this->getEventQueue()->insertEvent(new CreatePassengerEvent(Config::addSeconds(eventPtr->getEventTime(), 15),
                                                                    new Passenger()));
    }

}

void System::handleEvent(PassengerArriveDestinationEvent* eventPtr) {

    std::cout << eventPtr->printDetails() << std::endl;


}