//
// Created by Grisha on 09.03.2021.
//

#ifndef LAB2_MYDYNAMICARRAY_H
#define LAB2_MYDYNAMICARRAY_H
#include "cstring"
#include <string>
#include <iostream>

template <class T>
class myDynamicArray {
private:
    T *arr;                           //массив элементов, с которыми работает пользователь
    int len;                          //длина массива (количество элементов, достуных пользователю)
    int size;                         //количество элементов, под которые выделена память
    const size_t elSize = sizeof(T);
public:
    class IndexOutOfRange{
    public:
        int length;
        int index;
        IndexOutOfRange(int length, int index): length(length), index(index) {};
        IndexOutOfRange(): length(-1), index(-1) {};
    };

//    friend



    myDynamicArray(T *items, int count);

    explicit myDynamicArray(int size);

    myDynamicArray();

    myDynamicArray(myDynamicArray<T> const &dynamicArray);

    explicit myDynamicArray(myDynamicArray<T> *dynamicArray);

    ~myDynamicArray();

    int length() const;

    T get(int index) const;

    int getSize() const {
        return size;
    }

    void reverse() {
        for (auto i = 0; i < len / 2; i++) {
            int index = len - 1 - i;
            T item = arr[i];
            arr[i] = arr[index];
            arr[index] = item;
        }
    }

    T &operator [] (int index);

    myDynamicArray<T> &operator = (myDynamicArray<T> dynamicArray) {
        resize(dynamicArray.len);
        for (int i = 0; i < len; i++) {
            arr[i] = dynamicArray.arr[i];
        }
        return *this;
    }

    myDynamicArray<T> &operator = (myDynamicArray<T> *dynamicArray) {
        arr = dynamicArray->arr;
        len = dynamicArray->len;
        size = dynamicArray->size;

        return *this;
    }

    myDynamicArray<T> &operator* () {
        return *this;
    }

    int operator == (myDynamicArray<T> dynamicArray) const {
        if (len != dynamicArray.length()) return 0;

        for (int i = 0; i < len; i++) {
            if (arr[i] != dynamicArray.arr[i])
                return 0;
        }
        return 1;
    }

    T *begin() const;

    T *end() const;

    void set(T item, int index);

    void resize(int newSize);

    myDynamicArray<myDynamicArray<T>*> *split(T item) {
        myDynamicArray<int> indexes;

        for (int i = 0; i < len; i++) {
            if (arr[i] == item) {
                indexes.resize(indexes.length() + 1);
                indexes[indexes.length() - 1] = i;
            }
        }

        indexes.resize(indexes.length() + 1);
        indexes[indexes.length() - 1] = len;

        auto res = new myDynamicArray<myDynamicArray<T>*>;

        res->resize(indexes.length());

        int index = 0;
        auto *element = new myDynamicArray<T>;
        element->resize(indexes[index]);

        for (int i = 0, j = 0; i < len; i++, j++) {
            if (i == indexes[index]) {
                res[0][index] = element;
                element = new myDynamicArray<T>;
                index++;
                element->resize(indexes[index] - indexes[index - 1] - 1);
                j = -1;
                continue;
            }
            element[0][j] = arr[i];
        }
        res[0][index] = element;
        return res;
    }

    int find(T item) const {
        if (len == 0) throw  IndexOutOfRange(0, 0);

        for (int i = 0; i < len; i++) {
            if (arr[i] == item)
                return i;
        }
        return -1;
    }

    int find(const myDynamicArray<T> *dynamicArray) const {
        if (len == 0) throw IndexOutOfRange(0, 0);
        if (dynamicArray->len == 0) throw IndexOutOfRange(0, 0);

        if (len < dynamicArray->len) return -1;

        int count = 0;

        for (int i = 0; i < len; i++) {
            if (i + dynamicArray->len > len && count == 0)
                break;

            if (count == dynamicArray->len) {
                return i - count;
            }

            if (arr[i] == dynamicArray->arr[count]) {
                count++;
            }
            else {
                count = 0;
            }
        }

        return -1;
    }

    template<class U>
    myDynamicArray<U>* map(U (*func)(T item)) {
        auto *res = new myDynamicArray<U>;
        res->resize(len);
        for (int i = 0; i <len; i++) {
            (*res)[i] = func(arr[i]);
        }

        return res;
    }

    template<class U>
    myDynamicArray<U>* map(T item, U (*func)(T item1, T item2)) {
        auto *res = new myDynamicArray<U>;
        res->resize(len);
        for (int i = 0; i < len; i++) {
            (*res)[i] = func(arr[i], item);
        }

        return res;
    }

    template<class U>
    T reduce(U (*func)(T item1, T item2)) {
        if (len < 2) throw IndexOutOfRange(len, 1);

        auto res = func(arr[0], arr[1]);
        for (int i = 2; i < len; i++) {
            res = func(res, arr[i]);
        }

        return res;
    }

    myDynamicArray<myDynamicArray<T>>* zip(myDynamicArray<T> *arr1) {
        auto *res = new myDynamicArray<myDynamicArray<T>>;
        if (arr1->length() == 0 || len == 0) throw IndexOutOfRange(0, 0);
        int min = len < arr1->length() ? len : arr1->length();
        res->resize(min);
        for (int i = 0; i < min; i++) {
            (*res)[i].resize(2);
            (*res)[i][0] = arr[i];
            (*res)[i][1] = (*arr1)[i];
        }

        return res;
    }

    template<class U>
    static myDynamicArray<myDynamicArray<U>> *unzip(myDynamicArray<myDynamicArray<U>> *dynamicArray) {
        auto *res = new myDynamicArray<myDynamicArray<U>>;
        res->resize(2);
        int dlen = dynamicArray->length();
        (*res)[0].resize(dlen);
        (*res)[1].resize(dlen);
        int i;
        for (i = 0; i < dlen; i++) {
            if ((*dynamicArray)[i].length() < 2) break;

            (*res)[0][i] = (*dynamicArray)[i][0];
            (*res)[1][i] = (*dynamicArray)[i][1];
        }
        if (i != dlen) {
            (*res)[0].resize(i);
            (*res)[1].resize(i);
        }

        return res;
    }
};

template<class T>
std::ostream &operator << (std::ostream &cout, const myDynamicArray<T> &dynamicArray) {
    cout << '{';
    for (int i = 0; i < dynamicArray.length(); i++) {
        cout << dynamicArray[i];
        if (i < dynamicArray.length() - 1) {
            cout << ", ";
        }
    }
    return cout << '}';
}

template<class T>
std::ostream &operator << (std::ostream &cout, myDynamicArray<T> *dynamicArray) {
    return cout << dynamicArray[0];
}

#endif //LAB2_MYDYNAMICARRAY_H
