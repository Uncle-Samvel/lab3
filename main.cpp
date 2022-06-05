#include <iostream>
#include "menuTree.h"
#include "menuSet.h"

using namespace std;
int main() {
/*
    int count = 400000;

    string str;
    for (int i = 0; i < 10000; i++) {
        str += (char) (i % 256);
    }

    clock_t time1, time2;
    time1 = clock();
    for (int i = 0; i < count; i++) {
        func1(str);
    }
    time2 = clock();
    cout << time2 - time1 << endl;

    time1 = clock();
    for (int i = 0; i < count; i++) {
        func2(str);
    }
    time2 = clock();
    cout << time2 - time1 << endl;

    time1 = clock();
    for (int i = 0; i < count; i++) {
        func3(&str);
    }
    time2 = clock();
    cout << time2 - time1 << endl;

    return 0;
*/

    while (true) {
        cout << "Введите номер для выбора режима работы меню:\n"
                "\t0: для выхода из программы\n"
                "\t1: для работы с бинарным деревом\n"
                "\t2: для работы с множеством\n: ";
        int item = getInt(0, 2);
        if (item == 0)
            break;

        switch (item) {
            default: break;
            case 1:
                mainMenuBinaryTree();
                break;
            case 2:
                mainMenuSet();
                break;
        }

    }
    return 0;

}