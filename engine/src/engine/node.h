//
// Created by chian on 2021-06-01.
//

#include <iostream>

#ifndef BUSSIM_NODE_H
#define BUSSIM_NODE_H

template <class T>
class Node {
private:
    Node<T>* prePtr;
    T* containPtr;
    Node<T>* postPtr;
public:
    Node() {
        this->containPtr = NULL;
        this->prePtr = NULL;
        this->postPtr = NULL;
    }

    Node(T* containPtr) {
        this->containPtr = containPtr;
        this->prePtr = NULL;
        this->postPtr = NULL;
    }

    ~Node() {
        if (this->containPtr != NULL) {
            delete this->containPtr;
        }
    }

    Node<T> *getPrePtr() const {
        return prePtr;
    }

    void setPrePtr(Node *prePtr) {
        Node::prePtr = prePtr;
    }

    T *getContainPtr() const {
        return containPtr;
    }

    void setContainPtr(T *containPtr) {
        Node::containPtr = containPtr;
    }

    Node<T> *getPostPtr() const {
        return postPtr;
    }

    void setPostPtr(Node *postPtr) {
        Node::postPtr = postPtr;
    }
};
#endif //BUSSIM_NODE_H
