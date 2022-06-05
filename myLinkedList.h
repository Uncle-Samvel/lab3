//
// Created by Grisha on 09.03.2021.
//

#ifndef LAB2_MYLINKEDLIST_H
#define LAB2_MYLINKEDLIST_H

#include "cstdlib"
#include <iostream>

template<class T>
class myLinkedList {
private:
    typedef struct Element {        //структура одного элемента связного списка
        T data;                     // * данные, хранящиеся в одном элементе
        struct Element *next;       // * ссылка на следующий элемент
    } element;

    int len = 0;                    //длина связного списка

    element *head = nullptr;        //ссылка на начало списка
    element *ending = nullptr;      //ссылка на конец списка
public:
    class IndexOutOfRange{
    public:
        int length;
        int index;
        IndexOutOfRange(int length, int index): length(length), index(index) {};
        IndexOutOfRange(): length(-1), index(-1) {};
    };

    class Iterator {               //класс итератора, для работы итератора со связным списком
    private:
        myLinkedList<T> *list;
        element *el;
    public:
        Iterator(): list(nullptr), el(nullptr) {}
        explicit Iterator(myLinkedList<T> *linkedList): list(linkedList), el(linkedList->head) {}
        explicit Iterator(myLinkedList<T> *linkedList, element *elem): list(linkedList), el(elem) {}
        friend myLinkedList<T>;

        T &operator*() const {
            return el->data;
        }

        int operator == (const Iterator& iter) const {
            return list == iter.list && el == iter.el;
        }

        int operator != (const Iterator& iter) const {
            return !(*this == iter);
        }

        Iterator& operator++() {
            if (el != nullptr)
                el = el->next;
            return *this;
        }


        Iterator begin() const {
            return Iterator(list);
        }

        Iterator end() const {
            return Iterator(list, nullptr);
        }

//        void operator() (myLinkedList<T> *linkedList) {
//            list = linkedList;
//            el = linkedList->head;
//        }

        Iterator& operator = (Iterator iterator) {
            list = iterator.list;
            el = iterator.el;
            return *this;
        }
    };

    void append(T item);

    void prepend(T item);

    void insert(T item, int index);

    void set(T item, int index);

    myLinkedList(T *items, int count);

    explicit myLinkedList(T item);

    myLinkedList();

    myLinkedList(myLinkedList<T> const &linkedList);

    ~myLinkedList();

    T getFirst();

    T getLast();

    T get(int index);

    T &operator [] (int index);

    myLinkedList<T> getSubList(int startIndex, int endIndex);

    int length();

    T pop();

    T pop(int index);

    void Delete() {
        Element *element;
        while (head != nullptr) {
            element = head;
            head = head->next;
            delete element;
        }
        ending = nullptr;
        len = 0;
    }

    myLinkedList<T>& operator = (const myLinkedList<T>& linkedList) {
        Delete();

        for (element *elem = linkedList.head; elem; append(elem->data), elem = elem->next);

        return *this;
    }

    myLinkedList<T>& operator = (myLinkedList<T> *linkedList) {
        Delete();
        head = linkedList->head;
        ending = linkedList->ending;
        len = linkedList->len;
    }

    myLinkedList<T>& operator *() {
        return *this;
    }

    myLinkedList<myLinkedList<T>*>* split(T item) {
        auto res = new myLinkedList<myLinkedList<T>*>;
        auto elem = new myLinkedList<T>;
        for (auto &i : iter) {
            if (i == item) {
                res->append(elem);
                elem = new myLinkedList<T>;
                continue;
            }
            elem->append(i);
        }
        res->append(elem);
        return res;
    }

    int find(T item) {
        if (len == 0) throw IndexOutOfRange(0, 0);
        element *elem = head;
        int index = 0;
        while(elem != nullptr) {
            if (elem->data == item)
                return index;
            elem = elem->next;
            index++;
        }
        return -1;
    }

    int find(myLinkedList<T> *linkedList) {
        if (linkedList->len == 0) throw IndexOutOfRange(0, 0);
        if (len == 0) throw IndexOutOfRange(0, 0);

        if (len < linkedList->len) return -1;

        element *elem = head;
        element *compare = linkedList->head;
        int index = 0;
        int count = 0;
        while (elem != nullptr) {
            if (count == linkedList->len)  //мы нашли подпоследовательность, которая начинается с элемента index
                return index;

            if (index + len > linkedList->len)  //у нас осталось для обхода меньше элементов, чем содержится в linkedList
                break;

            if (elem->data == compare->data) {
                count++;
                compare = compare->next;
            }
            else {
                index++;

                if (count != 0) {
                    compare = linkedList->head;
                    index += count;
                    count = 0;
                }
            }

            elem = elem->next;
        }

        return -1;
    }

    void reverse() {
        element *myEnding = head;
        element *elem;
        element *next;
        element *previous = head;
        for (elem = myEnding->next; elem != nullptr;) {
            next = elem->next;
            elem->next = previous;
            previous = elem;
            elem = next;
        }
        myEnding->next = nullptr;

        head = ending;
        ending = myEnding;
    }

    myLinkedList<T>* concat(myLinkedList<T> *linkedList) {
        for (auto &i : linkedList) {
            append(i);
        }
        return this;
    }

    myLinkedList<T> *concat_(myLinkedList<T> *linkedList) {
        auto *res = new myLinkedList<T>(*this);
        res->concat(linkedList);
        return res;
    }

    Iterator begin() const {
        return iter.begin();
    }

    Iterator end() const {
        return iter.end();
    }

    Iterator iter;
};

template<class T>
std::ostream &operator << (std::ostream &cout, myLinkedList<T> linkedList) {
    for (auto &i : linkedList) {
        cout << i << ", ";
    }
    return cout << "\b\b}";
}

template<class T>
std::ostream &operator << (std::ostream &cout, myLinkedList<T> *linkedList) {
    return cout << *linkedList;
}

#endif //LAB2_MYLINKEDLIST_H
