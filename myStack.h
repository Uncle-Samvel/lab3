//
// Created by Grisha on 30.04.2021.
//

#ifndef LAB3_MYSTACK_H
#define LAB3_MYSTACK_H

#include "../Sources/myLinkedList.cpp"

template<class T>
class myStack {
private:
    myLinkedList<T> elements;
public:
    class IndexOutOfRange {};

    myStack() = default;

    myStack(const myStack<T>& stack): elements(stack.elements) {}

    explicit myStack(myStack<T>* stack): elements(stack->elements) {}

    explicit myStack(T element): elements(myLinkedList<T>(element)) {}

    explicit myStack(myLinkedList<T> *list): elements(*list) {}

    myStack(T* elements, int count) {
        for (int i = 0; i < count; i++) {
            add(elements[i]);
        }
    }

    void add(T element) {
        elements.prepend(element);
    }

    void add(const myStack<T>& stack) {
        elements = stack.elements.concat_(&elements);
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


#endif //LAB3_MYSTACK_H
