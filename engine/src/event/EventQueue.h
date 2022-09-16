//
// Created by chian on 2021-06-16.
//

#ifndef BUSSIM_EVENTQUEUE_H
#define BUSSIM_EVENTQUEUE_H

#include "engine/linkedList.h"
#include "BaseEvent.h"

class EventQueue {
private:

    LinkedList<BaseEvent>* eventQueueListPtr = NULL;

public:
    EventQueue();
    ~EventQueue();

    void insertEvent(BaseEvent* event);

    bool isEmpty();

    BaseEvent* popUpEvent();

    void printQueue();
};

#endif //BUSSIM_EVENTQUEUE_H
