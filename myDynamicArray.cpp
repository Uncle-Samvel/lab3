//
// Created by Grisha on 09.03.2021.
//

#include "../Headers/myDynamicArray.h"

#ifndef LAB2_MYDYNAMICARRAY_CPP
#define LAB2_MYDYNAMICARRAY_CPP

template<class T>
void arrCopy(T *arr_in, T *arr_out, int count) {
    for (int i = 0; i < count; i++) {
        arr_in[i] = arr_out[i];
    }
}

template<class T>
myDynamicArray<T>::myDynamicArray(T *items, int count) {
    arr = nullptr;
    size = 0;
    len = 0;
    if (count < 0) {return;}                       //создание нового пустого массива и копирование в него данных из исходного
    resize(count);
    //memcpy(arr, items, len * elSize);
    for (int i = 0; i < len; i++) {
        arr[i] = items[i];
    }
}

template<class T>
myDynamicArray<T>::myDynamicArray(int newSize) {   //создание нового пустого массива размера size
    size = 0;
    arr = nullptr;
    len = 0;
    if (newSize <= 0) {len = 0; return;}
    resize(newSize);
}

template<class T>
myDynamicArray<T>::myDynamicArray() {
    arr = nullptr;
    len = 0;
    size = 0;
}

template<class T>
myDynamicArray<T>::myDynamicArray(const myDynamicArray<T> &dynamicArray) { //создание нового массива и копирование элементов из такого же класса
    arr = nullptr;
    size = 0;
    len = 0;
    if (dynamicArray.len == 0) {
        return;
    }
    resize(dynamicArray.len);
    //memcpy(arr, dynamicArray.arr, len * elSize);
    for (int i = 0; i < len; i++) {
        arr[i] = dynamicArray.arr[i];
    }
}


template<class T>
myDynamicArray<T>::myDynamicArray(myDynamicArray<T> *dynamicArray) {     //копирование элементов по ссылке на массив
    len = dynamicArray->len;
    arr = dynamicArray->arr;
    size = dynamicArray->size;
}

template<class T>
myDynamicArray<T>::~myDynamicArray() {      //удаление массива
    delete[] arr;
}

template<class T>
int myDynamicArray<T>::length() const {           //вывод длины массива
    return len;
}

template<class T>
T myDynamicArray<T>::get(int index) const {       //получение элемента по индексу
    if (index < 0 || index >= len) throw IndexOutOfRange(len, index);  //исключение выхода за массив

    return arr[index];
}

template<class T>
T &myDynamicArray<T>::operator[](int index) {
    if (index < 0 || index >= len) throw IndexOutOfRange(len, index);  //исключение выхода за массив

    return arr[index];
}

template<class T>
void myDynamicArray<T>::set(T item, int index) {  //задание элемента по индексу
    if (index < 0 || index >= len) throw IndexOutOfRange(len, index); //исключение выхода за массив

    arr[index] = item;
}

template<class T>
void myDynamicArray<T>::resize(int newSize) {
    if (newSize < 0) throw IndexOutOfRange(len, newSize); //исключение выхода за массив
    if (len == newSize) return;               //длина не изменилась
    if (newSize == 0) {                       //нулевая длина, удаление массива
        if (arr != nullptr)
            delete[] arr;
        len = 0;
        size = 0;
        arr = nullptr;
        return;
    }
    if (newSize > size) {                     //создание нового массива с выделением памяти и заполнение данных
        if (size == 0) size = 1;
        for (size; size <= newSize + 1; size *= 2);
        int newSize2 = newSize;
        T *arrNew = new T[size];
        if (arr != nullptr) {
            arrCopy<T>(arrNew, arr, len);
            delete[] arr;
        }
        newSize = newSize2;
        arr = arrNew;
    }
    else if (newSize < size / 3) {            //создание нового массива с освобождением памяти и заполнение данных
        for (size; size / 3 > newSize + 1; size /= 2);
        T *arrNew = new T[size];
        if (arr != nullptr) {
            arrCopy<T>(arrNew, arr, newSize);
            delete[] arr;
        }
        arr = arrNew;
    }
    /**/
    len = newSize;
}

template<class T>
T *myDynamicArray<T>::begin() const {  //функция для работы итератора
    return arr;
}

template<class T>
T *myDynamicArray<T>::end() const {    //функция для работы итератора
    return arr ? arr + len : nullptr;
}

#endif