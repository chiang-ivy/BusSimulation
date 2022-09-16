#include <iostream>
#include "rapidjson/writer.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include <cstdio>

#include <config/config.h>
#include <config/bus_system.h>
#include <engine/node.h>
#include <engine/linkedList.h>
#include <event/BusStartServiceEvent.h>
#include <cstdlib>
#include <object/System.h>
#include <object/Bus.h>
#include <event/EventQueue.h>
#include <object/Passenger.h>
#include <string.h>

using namespace rapidjson;

int main()
{

    Config* config = new Config();

    config->processConfigJson();

    System* system = new System();

    system->createAllBusStopList();

    // system.printDetail(); // Test code
    //system.resetBusStopListMap(); //Test code for memory leak issue

    std::cout << "System start time: " << Config::convertTimeToStr(BusSystem::getBusSystem()->getStartTime()) << std::endl;
    std::cout << "System end   time: " << Config::convertTimeToStr(BusSystem::getBusSystem()->getEndTime()) << std::endl;

    std::cout << "Line A: interval : " << (*(BusSystem::getBusSystem()->getBusLinesMapPtr()))['a']->getBusInterval() << std::endl;


    EventQueue* eventQ = system->getEventQueue();

    system->setupStartQueue();

    while (!eventQ->isEmpty()) {
        BaseEvent* baseEventPtr = eventQ->popUpEvent();

        system->eventHandler(baseEventPtr);

    }

    system->resetBusStopListMap(); // Clear all the BusStopList in Map structure.

    delete config;
    delete BusSystem::getBusSystem();
    delete system;

    return 0;
}