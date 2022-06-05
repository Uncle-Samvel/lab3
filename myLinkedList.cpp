//
// Created by Grisha on 09.03.2021.
//


#ifndef LAB2_MYLINKEDLIST_CPP
#define LAB2_MYLINKEDLIST_CPP

#include "../Headers/myLinkedList.h"

template<class T>
void myLinkedList<T>::append(T item) {  //добавление элемента в конец списка
    auto *el = new element;             //создание элемента с входными данными
    el->data = item;
    el->next = nullptr;
    len++;
    if (head == nullptr) {              //проверка на пустоту списка
        head = el;
        ending = el;
        return;
    }
    ending->next = el;                     //добавление элемента в конец
    ending = el;
}

template<class T>
void myLinkedList<T>::prepend(T item) { //добавление в начало
    auto *el = new element;             //создание нового элемента и заполнение
    el->data = item;
    el->next = head;
    len++;
    if (head == nullptr) {
        head = el;
        ending = el;
        return;
    }
    head = el;
}

template<class T>
void myLinkedList<T>::insert(T item, int index) {
    if (index < 0 || index >= len) throw IndexOutOfRange(len, index);

    if (index == 0) {
        prepend(item);
        return;
    }
    if (index == len - 1) {
        append(item);
        return;
    }

    element *el = head;

    for (int i = 0; i < index - 1; i++, el = el->next);

    auto *elNew = new element;
    elNew->next = el->next;
    elNew->data = item;
    el->next = elNew;
    len++;
}

template<class T>
void myLinkedList<T>::set(T item, int index) {
    operator[](index) = item;
}

template<class T>
myLinkedList<T>::myLinkedList(T *items, int count) {
    if (count < 0) throw IndexOutOfRange(0, count);
    for (int i = 0; i < count; i++) {
        append(items[i]);
    }
    iter.list = this;
    iter.el = head;
}

template<class T>
myLinkedList<T>::myLinkedList(myLinkedList<T> const &linkedList) {
    element *el = linkedList.head;
    while (el != nullptr) {
        append(el->data);
        el = el->next;
    }
    iter.list = this;
    iter.el = head;
}


template<class T>
myLinkedList<T>::myLinkedList(T item) {
    append(item);
    iter.list = this;
    iter.el = head;
}

template<class T>
T myLinkedList<T>::getFirst() {
    if (head == nullptr) throw IndexOutOfRange(len, 0); //обработка ошибки

    return head->data;
}

template<class T>
T myLinkedList<T>::getLast() {
    if (ending == nullptr) throw IndexOutOfRange(len, len - 1); //обработка ошибки

    return ending->data;
}

template<class T>
myLinkedList<T> myLinkedList<T>::getSubList(int startIndex, int endIndex) {
    if (startIndex < 0 || startIndex >= len) throw IndexOutOfRange(len, startIndex);
    if (endIndex < 0 || endIndex >= len) throw IndexOutOfRange(len, endIndex);

    myLinkedList<T> newLinkedList = myLinkedList<T>();
    for (int i = startIndex; i < endIndex; i++) {
        newLinkedList.append(get(i));
    }

    return newLinkedList;
}

template<class T>
int myLinkedList<T>::length() {
    return len;
}

template<class T>
myLinkedList<T>::myLinkedList() {
    len = 0;
    head = nullptr;
    ending = nullptr;
    iter.list = this;
    iter.el = head;
}

template<class T>
T myLinkedList<T>::pop() {
    return pop(len - 1);
}

template<class T>
T myLinkedList<T>::pop(int index) {
    if (index < 0 || index >= len) throw IndexOutOfRange(len, index); //обработка ошибки

    element *el = head;
    element *prev = nullptr;

    T data;

    for (int i = 0; i < index; i++, prev = el, el = el->next);

    data = el->data;

    if (prev == nullptr) {
        head = head->next;
    }
    else if (el == ending) {
        prev->next = nullptr;
        ending = prev;
    }
    else {
        prev->next = el->next;
    }
    delete el;
    len--;
    if (len == 0) {
        head = nullptr;
        ending = nullptr;
    }
    return data;
}

template<class T>
myLinkedList<T>::~myLinkedList() {
    if (len < 0)
        Delete();
}

template<class T>
T &myLinkedList<T>::operator[](int index) {
    if (index < 0 || index >= len) throw IndexOutOfRange(len, index); //обработка ошибки

    element *el = head;

    T data;

    for (int i = 0; i < index; i++, el = el->next);
    return el->data;
}

template<class T>
T myLinkedList<T>::get(int index) {
    return (*this)[index];
}


#endif //LAB2_MYLINKEDLIST_CPP
