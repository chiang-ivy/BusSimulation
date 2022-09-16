//
// Created by chian on 2021-06-01.
//

#include "BaseEvent.h"

BaseEvent::BaseEvent(const char* eventTime) {
    this->eventTime = Config::convertStrToTime(eventTime);
}

BaseEvent::~BaseEvent() {
}

time_t BaseEvent::getEventTime() const {
    return eventTime;
}
