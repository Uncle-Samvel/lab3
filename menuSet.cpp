//
// Created by Grisha on 12.04.2021.
//

#include "menuSet.h"

using namespace std;

template<class T>
void printArr(myArraySequence<mySet<T>*> *arr) {
    for (int i = 0; i < arr->length(); i++) {
        cout << i << ": " << *arr->get(i) << endl;
    }
    cout << endl;
}

void mainMenuSet() {
    myArraySequence<mySet<int>*>          arrInt;
    myArraySequence<mySet<float>*>        arrFloat;
    int item;
    while(true) {
        cout << "Программа имеет следующие возможности: \n"
             << "\t1: Ввести и запомнить множество\n"
             << "\t2: Выполнить операцию над множествами\n"
             << "\t3: Вывести множество в консоль\n"
             << "\t4: Удалить или переместить множества в памяти\n"
             << "\t5: Запустить функцию тестирования множеств\n"
             << "\t6: Закончить выполнение функции\n"
             << "Введите число: ";
        cin >> item;
        if (item < 1 || item > 6) {
            cout << "Ошибка! Нет такого пункта! Повторите попытку\n";
            continue;
        }

        if (item == 6)
            break;

        switch (item) {
            case 1: readSet(&arrInt, &arrFloat); break;
            case 2: operationWithSet(&arrInt, &arrFloat); break;
            case 3: printSet(&arrInt, &arrFloat); break;
            case 4: deleteSet(&arrInt, &arrFloat); break;
            case 5: testFuncSet(); break;
            default: break;
        }
    }

    for (auto &i : arrInt) {
        delete i;
    }

    for (auto &i : arrFloat) {
        delete i;
    }
}

//1
void readSet(myArraySequence<mySet<int>*> *intArr,
                    myArraySequence<mySet<float>*> *floatArr){

    int count = 0;

    cout << "Введите колличество элементов множества или -1 для выхода\n: ";
    do {
        if (count < 0) {
            cout << "Количество элементов не может быть отрицательным!\n: ";
        }
        cin >> count;

        if (count == -1)
            return;
    } while(count < 0);

    auto item = getType();
    if (item == 0) return;

    cout << "Сгенерировать множество автоматически или ввести вручную?:\n"
            "\t0: выход\n"
            "\t1: ввести множество вручную\n"
            "\t2: сгенерировать множество\n: ";

    int item2 = getInt(0, 2);
    if (item2 == 0) return;

    if (item2 == 1) {
        switch (item) {
            case 1:
                readTypeSet<int>(intArr, count);
                break;
            case 2:
                readTypeSet<float>(floatArr, count);
                break;
            default:
                break;
        }
    }

    if (item2 == 2) {
        switch (item) {
            case 1:
                generateRandomSet<int>(intArr, count, randomInt);
                break;
            case 2:
                generateRandomSet<float>(floatArr, count, randomFloat);
                break;
            default:
                break;
        }
    }

    cout << "Хотите ввести ещё одно множество?\n"
            "\t0 - нет\n"
            "\t1 - да\n: ";

    item = getInt(0, 1);
    if (item) {
        readSet(intArr, floatArr);
    }
}

template<class T>
void readTypeSet(myArraySequence<mySet<T>*> *arr, int count) {
    cout << "Введите элементы множества\n:";
    myArraySequence<T> element;
    for (int i = 0; i < count; i++) {
        T item;
        cin >> item;
        element.append(item);
    }

    cout << "Вы ввели: " << mySet<T>(element)
         << "\nЗаписать это множество? (1 - да, 0 - повторить попытку ввода, "
         << "другое число приведёт к выходу их функции)\n:";
    int item;
    cin >> item;

    switch (item) {
        default: break;
        case 0: readTypeSet<T>(arr, count); break;
        case 1:
            auto *res = new mySet<T>;
            *res = mySet<T>(element);
            arr->append(res);
            break;
    }
}

template<class T>
void generateRandomSet(myArraySequence<mySet<T>*> *arr, int count, T (*func)()) {
    myArraySequence<T> element;
    for (int i = 0; i < count; i++) {
        element.append(func());
    }
    mySet<T> set(element);
    cout << "Сгенерировано \"" << set << "\". Записать или сгенерировать новое?\n"
            "\t-1: выход\n"
            "\t 0: сгенерировать новое\n"
            "\t 1: записать множество в память\n: ";
    int item = getInt(-1, 1);
    switch (item) {
        default: break;
        case 0:
            generateRandomSet(arr, count, func);
            break;
        case 1:
            auto *res = new mySet<T>(element);
            arr->append(res);
            break;
    }
}

//2
void operationWithSet(myArraySequence<mySet<int>*> *intArr,
                             myArraySequence<mySet<float>*> *floatArr) {
    int type = getType();

    switch (type) {
        default: break;
        case 1: operationTypeWithSet<int>(intArr); break;
        case 2: operationTypeWithSet<float>(floatArr); break;
    }
}

template<class T>
void operationTypeWithSet(myArraySequence<mySet<T>*> *arr) {
    if (arr->length() == 0 ) {
        cout << "Таких множеств нет!\n";
        return;
    }
    int item;

    while(true) {
        auto len = arr->length();
        cout << "В памяти находится \"" << len << "\" множеств, введите:\n"
                "\t- число меньше нуля для выхода\n"
                "\t- индекс множества, для его выбора\n"
                "\t- число, больше чем число элементов, для вывода всем множеств\n: ";

        item = getInt();
        if (item < 0) break;

        if (item >= len) {
            printArr(arr);
            continue;
        }

        cout << "Вы выбрали: " << *arr->get(item) << endl;

        cout << "Какую операцию необходимо выполнить:\n"
                "\t0: выбрать другое множество\n"
                "\t1: объединить множества\n"
                "\t2: пересечь множества\n"
                "\t3: вычесть множества\n"
                "\t4: выполнить Жегалкинствое сложение для множеств\n"
                "\t5: скопировать множество\n: ";

        int item2 = getInt(0, 6);

        if (item2 == 0) continue;

        auto *Set1 = arr->get(item);
        mySet<T> *Set2, *Set3;

        if (item2 == 5) {
            Set3 = new mySet<T>;
            *Set3 = *Set1;
        }
        else {
            cout << "Введите:\n"
                    "\t-1: для выбора другого множества\n"
                    "\t- индекс множества для выполнения данной операции\n: ";

            int item3 = getInt(-1, len - 1);
            if (item3 == -1) {
                continue;
            }

            Set2 = arr->get(item3);
            Set3 = new mySet<T>;

            switch (item2) {
                default:
                    break;
                case 1:
                    *Set3 = *Set1 + *Set2;
                    break;
                case 2:
                    *Set3 = *Set1 * *Set2;
                    break;
                case 3:
                    *Set3 = *Set1 - *Set2;
                    break;
                case 4:
                    *Set3 = *Set1 ^ *Set2;
                    break;
            }
        }


        cout << "Было получено: \"" << *Set3 <<
                "\". Запомнить его под индексом \"" << len << "\" ?:\n"
                "\t0 - нет\n"
                "\t1 - да\n: ";

        item = getInt(0, 1);
        if (item == 1) {
            arr->append(Set3);
        }
        else {
            delete Set3;
        }
    }
}

//3
void printSet(myArraySequence<mySet<int>*> *intArr,
                     myArraySequence<mySet<float>*> *floatArr) {
    int type = getType();

    switch (type) {
        default: break;
        case 1:
            printTypeSet<int>(intArr);
            break;
        case 2:
            printTypeSet<float>(floatArr);
            break;
    }
}


template<class T>
void printTypeSet(myArraySequence<mySet<T>*> *arr) {
    if (arr->length() == 0) {
        cout << "Таких множеств нет!";
        return;
    }
    int item;
    do {
        cout << "В памяти находится \"" << arr->length() << "\" множеств этого типа, введите:\n"
                "\t- Индекс элемента для его вывода в консоль\n"
                "\t- Число, больше чем количество множеств для вывода всех множеств "
                "этого типа\n"
                "\t- Число меньше нуля для выхода из функции\n:";
        item = getInt();

        if (item < 0) break;

        if (item < arr->length()) {
            cout << item << ": " << *arr->get(item) << endl;
        }

        if (item >= arr->length())
            printArr(arr);

        cout << endl;
    } while (item >= 0);
}

//4
void deleteSet(myArraySequence<mySet<int>*> *intArr,
                      myArraySequence<mySet<float>*> *floatArr) {

    auto item = getType();
    if (item == 0) return;

    switch (item) {
        case 1: deleteTypeSet(intArr); break;
        case 2: deleteTypeSet(floatArr); break;
        default: break;
    }
}

template<class T>
void deleteTypeSet(myArraySequence<mySet<T>*> *arr) {
    if (arr->length() == 0) {
        cout << "Таких множеств нет!\n";
        return;
    }
    int item;

    while(true) {
        int len = arr->length();
        if (len == 0) {
            cout << "Больше не осталось множеств этого типа! Автоматический выход из функции\n";
            break;
        }
        cout << "В памяти находится \"" << len << "\" множеств, введите:\n"
                "\t- Число меньше нуля для выхода из функции\n"
                "\t- Индекс элемента, для его выбора\n"
                "\t- Число, больше длины массива, для вывода множеств в консоль\n: ";

        item = getInt();

        if (item < 0) break;

        if (item >= arr->length()) {
            printArr(arr);
            continue;
        }

        cout << "Выберите операцию:"
                "\t-1: вернуться к выбору индекса\n"
                "\t 0: для удаления элемента\n"
                "\t 1: для перемещения элемента на другое место\n: ";
        int item2 = getInt(-1, 1);

        if (item2 == -1) continue;

        if (item2 == 0) {
            cout << "Вы действительно хотите удалить \"" << *arr->get(item) << "\" ?\n"
                    "\t0 - нет\n"
                    "\t1 - да\n: ";
            item2 = getInt(0, 1);
            if (item2 == 1) {
                arr->pop(item);
            }
            continue;
        }

        cout << "Введите номер множества, с которым надо поменять \""
             << item << "\" множество\n: ";

        item2 = getInt(0, len - 1);
        if (item != item2) {
            mySet<T> *Set = arr->get(item);
            arr->set(arr->get(item2), item);
            arr->set(Set, item2);
        }
    }
}

//5
void testFuncSet() {
    cout << "Введите:\n"
            "\t- положительное число для ввода итераций тестов\n"
            "\t- нуль или отрицательное число для выхода\n: ";
    int count = getInt();
    if (count <= 0)
        return;

    test(count, 1);

    cout << "Хотите запустить тестирование ещё раз?\n"
            "\t0 - нет\n"
            "\t1 - да\n: ";
    count = getInt(0, 1);
    if (count == 1)
        testFuncSet();
}

#define funcTemplate(T) \
template void readTypeSet(myArraySequence<mySet<T>*> *arr, int count);                    \
template void generateRandomSet(myArraySequence<mySet<T>*> *arr, int count, T (*func)()); \
template void printTypeSet(myArraySequence<mySet<T>*> *arr);                              \
template void printArr(myArraySequence<mySet<T>*> *arr);                                  \
template void deleteTypeSet(myArraySequence<mySet<T>*> *arr);                             \
template void operationTypeWithSet(myArraySequence<mySet<T>*> *arr);                      \


funcTemplate(int)

funcTemplate(float)

/*
template void readTypeSet<int>(myArraySequence<mySet<int>*> *arr, int count);
template void readTypeSet<float>(myArraySequence<mySet<float>*> *arr, int count);
template void readTypeSet<complex<int>>(myArraySequence<mySet<complex<int>>*> *arr, int count);

template void printTypeSet<int>(myArraySequence<mySet<int>*> *arr);
template void printTypeSet<float>(myArraySequence<mySet<float>*> *arr);
template void printTypeSet<complex<int>>(myArraySequence<mySet<complex<int>>*> *arr);

template void printArr<int>(myArraySequence<mySet<int>*> *arr);
 */