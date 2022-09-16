//
// Created by chian on 2021-06-16.
//

#include "EventQueue.h"

EventQueue::EventQueue() {

    if (eventQueueListPtr == NULL)
        eventQueueListPtr = new LinkedList<BaseEvent>();
}

EventQueue::~EventQueue() {

    if (eventQueueListPtr != NULL) {
        delete eventQueueListPtr;
    }
}

void EventQueue::insertEvent(BaseEvent* event) {

    Node<BaseEvent>* nodePtr = new Node<BaseEvent>();
    nodePtr->setPrePtr(NULL);
    nodePtr->setPostPtr(NULL);
    nodePtr->setContainPtr(event);

    // Insert event by time stamp
    this->eventQueueListPtr->insertNodeByOrder(nodePtr);
}

bool EventQueue::isEmpty() {

    if (eventQueueListPtr->getSize() > 0) {
        return false;
    }
    else {
        return true;
    }
}

BaseEvent* EventQueue::popUpEvent() {

    Node<BaseEvent>* nodePtr =  this->eventQueueListPtr->popUpNode();

    BaseEvent* retEvent = NULL;

    if (nodePtr != NULL) {
        retEvent = nodePtr->getContainPtr();

        // Free Node memory
        nodePtr->setContainPtr(NULL);
        delete nodePtr;
    }

    return retEvent;
}

void EventQueue::printQueue() {

    Node<BaseEvent>* temp = this->eventQueueListPtr->getHead();

    std::cout << "*** Start dumping eventQueue" << std::endl;
    while (temp != NULL) {
        std::cout << temp->getContainPtr()->printDetails() << std::endl;

        temp = temp->getPostPtr();
    }
    std::cout << "*** End dumping eventQueue" << std::endl;
}