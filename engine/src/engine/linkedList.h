//
// Created by chian on 2021-06-01.
//

#ifndef BUSSIM_LINKEDLIST_H
#define BUSSIM_LINKEDLIST_H

#include "node.h"

template <class T>
class LinkedList {
private:
    Node<T>* head;
    int size;
public:
    LinkedList() {
        head = NULL;
        size = 0;
    }
    ~LinkedList() {}

    int getSize() {
        return size;
    }

    Node<T>* popUpNode() {

        Node<T>* ret = NULL;

        if (head != NULL) {
            ret = head;
            head = head->getPostPtr();

            if (head != NULL)
                head->setPrePtr(NULL);

            size--;
        }

        return ret;
    }

    void clear() {
        while (head != NULL) {

            Node<T>* next = head->getPostPtr();

            delete head;
            head = next;
        }

        head = NULL;
    }

    void printDetail() {
        Node<T>* temp = head;

        while (temp != NULL) {
            temp->getContainPtr()->printDetail();
            temp = temp->getPostPtr();
        }
    }

    void insertNodeAtBeginning(Node<T>* node) {
        node->setPrePtr(NULL);
        node->setPostPtr(head);
        head = node;

        size++;
    }

    void appendNodeAtTail(Node<T>* node) {
        Node<T>* temp = this->head;
        if (temp == NULL) {
            insertNodeAtBeginning(node);
        }
        else {

            while (temp->getPostPtr() != NULL ) {
                temp = temp->getPostPtr();
            }

            node->setPrePtr(temp);
            node->setPostPtr(NULL);
            temp->setPostPtr(node);

            size++;
        }
    }

    void removeNode(Node<T>* node) {

        if (node == NULL)
            return;

        if (node->getPrePtr() == NULL) { // Remove the node at the head of linked list
            this->head = node->getPostPtr();

            if (this->head != NULL) {
                this->head->setPrePtr(NULL);
            }

            node->setPostPtr(NULL);
        }
        else if (node->getPostPtr() == NULL) { //Remove the node at the tail of linked list
            node->getPrePtr()->setPostPtr(NULL);

            node->setPrePtr(NULL);
        }
        else { // Remove the node at the middle of linked list
            Node<T>* previousNode = node->getPrePtr();
            Node<T>* nextNode = node->getPostPtr();

            node->setPrePtr(NULL);
            node->setPostPtr(NULL);
            previousNode->setPostPtr(nextNode);
            nextNode->setPrePtr(previousNode);
        }

        size--;
    }

    void appendLinkedListAtTail(LinkedList<T>* linkedListPtr) {

        if (linkedListPtr->head == NULL) {
            linkedListPtr->size = 0;
        }

        if (linkedListPtr->getSize() > 0) {

            this->size += linkedListPtr->getSize();

            Node<T> *nodePtr = linkedListPtr->getHead();

            //this->appendNodeAtTail(nodePtr);

            if (this->getHead() == NULL) {
                this->head = nodePtr;
            }
            else {
                Node<T> *tempPtr = this->getHead();

                while (tempPtr->getPostPtr() != NULL) {
                    tempPtr = tempPtr->getPostPtr();
                }

                tempPtr->setPostPtr(nodePtr);
                nodePtr->setPrePtr(tempPtr);
            }


            linkedListPtr->setHeadToNULL();
        }
    }

    void insertNodeByOrder(Node<T>* node) {
        Node<T>* temp = this->head;

        bool inserted = false;

        while (temp != NULL && *(node->getContainPtr()) >= *(temp->getContainPtr())) {
            if (temp->getPostPtr() == NULL) {
                node->setPrePtr(temp);
                node->setPostPtr(NULL);
                temp->setPostPtr(node);
                inserted = true;
                break;
            }
            temp = temp->getPostPtr();
        }

        if (!inserted) {
            if (temp == NULL) { // Which means head is NULL, Ivy, do you know why?
                node->setPostPtr(NULL);
                node->setPrePtr(NULL);
                this->head = node;
            }
            else {
                // Insert the node into the Node before temp pointer
                Node<T>* temp2 = temp->getPrePtr();

                if (temp2 == NULL) { // When temp2 == NULL, looks like the insert point is at the head of linked list.
                                     // Ivy, do you know why?
                    node->setPostPtr(temp);
                    node->setPrePtr(NULL);
                    temp->setPrePtr(node);
                    head = node;
                }
                else {
                    temp2->setPostPtr(node);
                    node->setPostPtr(temp);
                    node->setPrePtr(temp2);
                    temp->setPrePtr(node);
                }
            }
        }

        size++;
    }

    Node<T>* getHead() {return head;}
    void setHeadToNULL() { head = NULL; }
};

#endif //BUSSIM_LINKEDLIST_H
