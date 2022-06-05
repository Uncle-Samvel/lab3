//
// Created by Grisha on 16.03.2021.
//

#ifndef LAB2_MYARRAYSEQUENCE_H
#define LAB2_MYARRAYSEQUENCE_H

#include "../Sources/myDynamicArray.cpp"

template<class T>
class myArraySequence {
private:
    myDynamicArray<T> dynamicArray;
public:
    class IndexOutOfRange{
    public:
        int length;
        int index;
        IndexOutOfRange(int length, int index): length(length), index(index) {};
        IndexOutOfRange(): length(-1), index(-1) {};
    };

    myArraySequence(T* items, int count) {
        dynamicArray = myDynamicArray<T> (items, count);
    }

    myArraySequence() {
        dynamicArray = myDynamicArray<T>();
    }

    explicit myArraySequence(T item) {
        dynamicArray = myDynamicArray<T>(&item, 1);
    }

    myArraySequence(const myArraySequence<T> &array) {
        dynamicArray = array.dynamicArray;
    }

    explicit myArraySequence(const myDynamicArray<T> &array) {
        dynamicArray = array;
    }

    T getFirst() const {
        if (length() == 0) throw IndexOutOfRange(length(), 0);
        return dynamicArray[0];
    }

    T getLast() const {
        if (length() == 0) throw IndexOutOfRange(length(), -1);
        return dynamicArray[dynamicArray.length() - 1];
    }

    T get(int index) const {
        if (index < 0 || index >= length()) throw IndexOutOfRange(length(), index);
        return dynamicArray.get(index);
    }

    void set(T item, int index) {
        if (index < 0 || index >= length()) throw IndexOutOfRange(length(), index);
        dynamicArray.set(item, index);
    }

    T pop() {
        if (dynamicArray.length() == 0) throw IndexOutOfRange(0, -1);
        T item = dynamicArray[dynamicArray.length() - 1];
        dynamicArray.resize(dynamicArray.length() - 1);
        return item;
    }

    T pop(int index) {
        if (index < 0 || index >= dynamicArray.length())
            throw IndexOutOfRange(dynamicArray.length(), index);

        T item = dynamicArray[index];
        for (int i = index; i < dynamicArray.length() - 1; i++) {
            dynamicArray[i] = dynamicArray[i+1];
        }
        dynamicArray.resize(dynamicArray.length() - 1);
        return item;
    }

    T &operator [] (int index) {
        if (index < 0 || index >= length())
            throw IndexOutOfRange(length(), index);

        return dynamicArray[index];
    }

    T *begin() const {
        return dynamicArray.begin();
    }

    T *end() const {
        return dynamicArray.end();
    }

    myArraySequence<T> &operator = (myArraySequence<T> arraySequence) {
        dynamicArray = arraySequence.dynamicArray;
        return *this;
    }

    myArraySequence<T> *operator*() {
        return this;
    }

    int operator == (myArraySequence<T> arraySequence) const {
        return dynamicArray == arraySequence.dynamicArray;
    }

    myArraySequence<T> *getSubSequence(int startIndex, int endIndex) {
        if (startIndex < 0 || startIndex >= length())
            throw IndexOutOfRange(length(), startIndex);
        if (endIndex < 0 || endIndex > length())
            throw IndexOutOfRange(length(), endIndex);

        int delta = startIndex < endIndex ? 1 : -1;

        auto newArray = new myArraySequence<T>;
        for (int i = startIndex; i != endIndex; i += delta) {
            newArray->append(dynamicArray[i]);
        }

        return newArray;
    }

    int length() const {
        return dynamicArray.length();
    }

    void append(T item) {
        dynamicArray.resize(dynamicArray.length() + 1);
        dynamicArray[length() - 1] = item;
    }

    void append(T *item) {
        append(*item);
        /*
        dynamicArray.resize(dynamicArray.length() + 1);
        dynamicArray[length() - 1] = *item;*/
    }

    void prepend(T item) {
        dynamicArray.resize(dynamicArray.length() + 1);
        for (int i = dynamicArray.length() - 2; i >= 0; i--) {
            dynamicArray[i+1] = dynamicArray[i];
        }
        dynamicArray[0] = item;
    }

    void prepend(T *item) {
        prepend(*item);
        /*
        dynamicArray.resize(dynamicArray.length() + 1);
        for (int i = dynamicArray.length() - 1; i >= 0; i--) {
            dynamicArray[i+1] = dynamicArray[i];
        }
        dynamicArray[0] = *item;*/
    }

    void remove() {
        dynamicArray.resize(0);
    }

    void remove(int from) {
        if (from < 0 || from >= dynamicArray.length()) throw IndexOutOfRange(dynamicArray.length(), from);
        dynamicArray.resize(from);
    }

    void remove(int from, int to) {
        if (from < 0 || from >= dynamicArray.length()) throw IndexOutOfRange(dynamicArray.length(), from);
        if (to < 0 || to >= dynamicArray.length()) throw IndexOutOfRange(dynamicArray.length(), to);

        if (from >= to) return;

        for (int i = 0; i + to < dynamicArray.length(); i++) {
            dynamicArray[i + from] = dynamicArray[i + to];
        }
        dynamicArray.resize(dynamicArray.length() - to + from);
    }

    void reverse() {
        dynamicArray.reverse();
    }

    void insert(T item, int index) {
        if (index < 0 || index >=dynamicArray.length()) throw IndexOutOfRange(dynamicArray.length(), index);
        dynamicArray.resize(dynamicArray.length() + 1);
        for (int i = dynamicArray.length() - 2; i >= index; i--) {
            dynamicArray[i+1] = dynamicArray[i];
        }
        dynamicArray[index] = item;
    }

    void insert(T *item, int index) {
        insert(*item, index);
        /*
        dynamicArray[index];
        dynamicArray.resize(dynamicArray.length() + 1);
        for (int i = dynamicArray.length() - 1; i >= index; i--) {
            dynamicArray[i+1] = dynamicArray[i];
        }
        dynamicArray[index] = *item;*/
    }

    myArraySequence<T> *concat(myArraySequence<T> *sequence) {
        int start = dynamicArray.length();
        dynamicArray.resize(start + sequence->length());

        for (int i = 0; i < sequence->length(); i++) {
            dynamicArray[i + start] = (*sequence)[i];
        }

        return this;
    }

    myArraySequence<T> *concat_(myArraySequence<T>* sequence) {
        auto *newArray = new myArraySequence<T>();
        newArray->dynamicArray = dynamicArray;

        int start = dynamicArray.length();
        newArray->dynamicArray.resize(start + sequence->length());

        for (int i = 0; i < sequence->length(); i++) {
            (*newArray)[i + start] = sequence->get(i);
        }
        return newArray;
    }

    myArraySequence<T> *operator + (myArraySequence<T>* sequence) {
        return concat_(sequence);
    }

    myArraySequence<T> *operator += (myArraySequence<T> *sequence) {
        concat(sequence);
        return this;
    }

    myArraySequence<myArraySequence<T>*> *split(T item) {
        auto res = new myArraySequence<myArraySequence<T>*>;
        auto element = new myArraySequence<T>;

        for (auto &i : dynamicArray) {
            if (i == item) {
                res->append(element);
                element = new myArraySequence<T>;
                continue;
            }
            element->append(i);
        }
        res->append(element);

        return res;
    }

    template<class U>
    myArraySequence<U> *map(U (*func)(T item)) {
        auto *res = new myArraySequence<U>;
        auto arr = dynamicArray.map(func);
        for (auto &i : *arr) {
            res->append(i);
        }
        delete arr;
        return res;
    }

    template<class U>
    myArraySequence<U> *map(T item, U (*func)(T item1, T item2)) {
        auto *res = new myArraySequence<U>;
        res->dynamicArray = dynamicArray.map(item, func);
        return res;
    }

    template<class U>
    U reduce(U (*func)(T item1, T item2)) {
        return dynamicArray.reduce(func);
    }

    myArraySequence<myArraySequence<T>> *zip(myArraySequence<T> *arraySequence) {
        auto *res = new myArraySequence<myArraySequence<T>>;
        auto min = dynamicArray.length() < arraySequence->length() ? dynamicArray.length() : arraySequence->length();

        for (int i = 0; i < min; i++) {
            myArraySequence<T> element;
            element.append(dynamicArray[i]);
            element.append(arraySequence->dynamicArray[i]);
            (*res).append(element);
        }

        return res;
    }

    template<class U>
    static myArraySequence<myArraySequence<U>> *unzip(myArraySequence<myArraySequence<U>> *arraySequence) {
        auto *res = new myArraySequence<myArraySequence<U>>;
        (*res).append(myArraySequence<U>());
        (*res).append(myArraySequence<U>());

        for (int i = 0; i < arraySequence->length(); i++) {
            if ((*arraySequence)[i].length() < 2) break;
            (*res)[0].append((*arraySequence)[i][0]);
            (*res)[1].append((*arraySequence)[i][1]);
        }

        return res;
    }

    int find(T item) const {
        return dynamicArray.find(item);
    }

    int find(myArraySequence<T> *sequence) const {
        myDynamicArray<T> array;
        array.resize(sequence->length());
        for (int i = 0; i < array.length(); i++) {
            array[i] = sequence->get(i);
        }
        return dynamicArray.find(&array);
    }
};

template<class T>
std::ostream &operator << (std::ostream &cout, myArraySequence<T> &arraySequence) {
    cout << '{';
    for (int i = 0; i < arraySequence.length(); i++) {
        cout << arraySequence[i];
        if (i != arraySequence.length() - 1) {
            cout << ", ";
        }
    }
    cout << '}';
    return cout;
}

template<class T>
std::ostream &operator << (std::ostream &cout, myArraySequence<T> *arraySequence) {
    return cout << *arraySequence;
}

#endif //LAB2_MYARRAYSEQUENCE_H
