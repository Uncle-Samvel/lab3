//
// Created by Grisha on 19.05.2021.
//

#ifndef LAB3_MYQUEUE_H
#define LAB3_MYQUEUE_H

#include "myLinkedList.h"
template<class T>
class myQueue {
private:
    myLinkedList<T> elements;
public:
    class IndexOutOfRange {};

    myQueue() = default;

    explicit myQueue(T element): elements(myLinkedList<T>(element)) {}

    explicit myQueue(const myLinkedList<T>& linkedList): elements(linkedList) {}

    myQueue(const myQueue<T>& queue): elements(queue) {}

    void add(T element) {
        elements.append(element);
    }

    void add(const myQueue<T>& queue) {
        elements.concat_(&queue.elements);
    }

    T get() {
        if (elements.length() == 0)
            throw IndexOutOfRange();

        return elements.pop(0);
    }

    int length() {
        return elements.length();
    }
};


#endif //LAB3_MYQUEUE_H
