//
// Created by chian on 2021-06-20.
//

#ifndef BUSSIM_PASSENGERARRIVEDESTINATIONEVENT_H
#define BUSSIM_PASSENGERARRIVEDESTINATIONEVENT_H

#include "CreatePassengerEvent.h"

class PassengerArriveDestinationEvent: public CreatePassengerEvent {
public:

    PassengerArriveDestinationEvent(time_t eventTime, Passenger* passengerPtr);
    ~PassengerArriveDestinationEvent();

    std::string printDetails();
};

#endif //BUSSIM_PASSENGERARRIVEDESTINATIONEVENT_H
