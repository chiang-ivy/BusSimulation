//
// Created by chian on 2021-06-19.
//

#ifndef BUSSIM_CREATEPASSENGEREVENT_H
#define BUSSIM_CREATEPASSENGEREVENT_H

#include "BaseEvent.h"
#include "object/Passenger.h"

class CreatePassengerEvent: public BaseEvent {
public:

    CreatePassengerEvent(time_t eventTime, Passenger* passengerPtr);
    ~CreatePassengerEvent();

    enum BaseEvent::EventType getEventType();
    std::string printDetails();

    Passenger *getPassengerPtr() const;

protected:

    Passenger* passengerPtr;
};

#endif //BUSSIM_CREATEPASSENGEREVENT_H
