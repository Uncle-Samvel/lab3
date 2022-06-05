//
// Created by Grisha on 28.05.2021.
//

#include "menuTree.h"

using namespace std;

template<class K, class T>
void printArr(myArraySequence<myBinaryTree<K, T>*> *arr) {
    for (int i = 0; i < arr->length(); i++) {
        cout << i << ": " << *arr->get(i) << endl;
    }
    cout << endl;
}

void mainMenuBinaryTree() {
    myArraySequence<myBinaryTree<int, int>*>     arrInt;
    myArraySequence<myBinaryTree<float, float>*> arrFloat;
    int item;
    while(true) {
        cout << "Программа имеет следующие возможности: \n"
             << "\t1: Ввести и запомнить дерево\n"
             << "\t2: Выполнить операцию над деревьями\n"
             << "\t3: Вывести дерево в консоль\n"
             << "\t4: Удалить или переместить деревья в памяти\n"
             << "\t5: Запустить функцию тестирования деревьев\n"
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
            case 1: readBinaryTree(&arrInt, &arrFloat); break;
            case 2: operationWithBinaryTree(&arrInt, &arrFloat); break;
            case 3: printBinaryTree(&arrInt, &arrFloat); break;
            case 4: deleteBinaryTree(&arrInt, &arrFloat); break;
            case 5: testFuncBinaryTree(); break;
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
void readBinaryTree(myArraySequence<myBinaryTree<int, int>*> *intArr,
             myArraySequence<myBinaryTree<float, float>*> *floatArr){

    int count = 0;

    cout << "Введите колличество элементов дерева или -1 для выхода\n: ";
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

    cout << "Сгенерировать дерево автоматически или ввести вручную?:\n"
            "\t0: выход\n"
            "\t1: ввести дерево вручную\n"
            "\t2: сгенерировать дерево\n: ";

    int item2 = getInt(0, 2);
    if (item2 == 0) return;

    if (item2 == 1) {
        switch (item) {
            case 1:
                readTypeBinaryTree<int, int>(intArr, count);
                break;
            case 2:
                readTypeBinaryTree<float, float>(floatArr, count);
                break;
            default:
                break;
        }
    }

    if (item2 == 2) {
        switch (item) {
            case 1:
                generateRandomBinaryTree<int, int>(intArr, count, randomInt, randomInt);
                break;
            case 2:
                generateRandomBinaryTree<float, float>(floatArr, count, randomFloat, randomFloat);
                break;
            default:
                break;
        }
    }

    cout << "Хотите ввести ещё одно дерево?\n"
            "\t0 - нет\n"
            "\t1 - да\n: ";

    item = getInt(0, 1);
    if (item) {
        readBinaryTree(intArr, floatArr);
    }
}

template<class K, class T>
void readTypeBinaryTree(myArraySequence<myBinaryTree<K, T>*> *arr, int count) {
    cout << "Введите ключи и элементы дерева\n:";
    myArraySequence<K> keys;
    myArraySequence<T> elements;
    for (int i = 0; i < count; i++) {
        K key;
        T item;
        cin >> key >> item;
        keys.append(key);
        elements.append(item);
    }
    myBinaryTree<K, T> binaryTree(keys, elements);
    cout << "Вы ввели: " << binaryTree
         << "\nЗаписать это дерево? (1 - да, 0 - повторить попытку ввода, "
         << "другое число приведёт к выходу их функции)\n:";
    int item;
    cin >> item;

    switch (item) {
        default: break;
        case 0: readTypeBinaryTree<K, T>(arr, count); break;
        case 1:
            arr->append(new myBinaryTree<K, T>(keys, elements));
            break;
    }
}

template<class K, class T>
void generateRandomBinaryTree(myArraySequence<myBinaryTree<K, T>*> *arr, int count, K (*funcK)(), T (*funcT)()) {
    myArraySequence<K> keys;
    myArraySequence<T> elements;
    for (int i = 0; i < count; i++) {
        keys.append(funcK());
        elements.append(funcT());
    }
    myBinaryTree<K, T> binaryTree(keys, elements);
    cout << "Сгенерировано:\n" << binaryTree.strLikeList() <<
            "\nЗаписать или сгенерировать новое?\n"
            "\t-1: выход\n"
            "\t 0: сгенерировать новое\n"
            "\t 1: записать дерево в память\n: ";
    int item = getInt(-1, 1);
    switch (item) {
        default: break;
        case 0:
            generateRandomBinaryTree(arr, count, funcK, funcT);
            break;
        case 1:
            auto *res = new myBinaryTree<K, T>(keys, elements);
            arr->append(res);
            break;
    }
}

//2
void operationWithBinaryTree(myArraySequence<myBinaryTree<int, int>*> *intArr,
                      myArraySequence<myBinaryTree<float, float>*> *floatArr) {
    int type = getType();

    switch (type) {
        default: break;
        case 1: operationTypeWithBinaryTree<int, int>(intArr); break;
        case 2: operationTypeWithBinaryTree<float, float>(floatArr); break;
    }
}

template<class K, class T>
void operationTypeWithBinaryTree(myArraySequence<myBinaryTree<K, T>*> *arr) {
    if (arr->length() == 0 ) {
        cout << "Таких деревьев нет!\n";
        return;
    }
    int item;

    while(true) {
        auto len = arr->length();
        cout << "В памяти находится \"" << len <<
                "\" деревьев, введите:\n"
                "\t- число меньше нуля для выхода\n"
                "\t- индекс дерева, для его выбора\n"
                "\t- число, больше чем число элементов, для вывода всем деревьев\n: ";

        item = getInt();
        if (item < 0) break;

        if (item >= len) {
            printArr(arr);
            continue;
        }

        cout << "Вы выбрали: " << *arr->get(item) << endl;

        cout << "Какую операцию необходимо выполнить:\n"
                "\t0: выбрать другое дерево\n"
                "\t1: добавить пару ключ/значение в дерево\n"
                "\t2: удалить ключ и его значение из дерева\n"
                "\t3: найти значение по ключу\n"
                "\t4: скопировать дерево\n"
                "\t5: извлечь поддерева\n"
                "\t6: проверить на вхождение поддерева\n: ";

        int item2 = getInt(0, 6);

        if (item2 == 0) continue;

        auto *BinaryTree1 = arr->get(item);

        if (item2 == 4 || item2 == 6) {
            cout << "Введите:\n"
                    "\t-1: для выбора другого дерева\n"
                    "\t- индекс дерева для выполнения данной операции\n: ";

            int item3 = getInt(-1, len - 1);
            if (item3 == -1) {
                continue;
            }

            myBinaryTree<K, T> *BinaryTree2, *BinaryTree3;

            switch (item2) {
                default: break;
                case 4:
                    BinaryTree3 = new myBinaryTree<K, T>;
                    *BinaryTree3 = *BinaryTree1;
                    arr->append(BinaryTree3);
                    break;
                case 6:
                    BinaryTree2 = arr->get(item3);
                    int res = BinaryTree1->inTree(*BinaryTree2);
                    if (res)
                        cout << "Данное дерево является поддеревом!\n";
                    else
                        cout << "Данное поддерево не было найдено!\n";
                    break;
            }
        }
        else {
            K key;
            T element;

            switch (item2) {
                default: break;
                case 1:
                    cout << "Введите пару ключ/значение\n: ";
                    cin >> key >> element;
                    BinaryTree1->insert(key, element);
                    cout << "Пара ключ/значение было добавлено!\n";
                    break;
                case 2:
                    cout << "Введите ключ\n: ";
                    cin >> key;
                    try {
                        BinaryTree1->remove(key);
                        cout << "Данный ключ был удалён!\n";
                    }
                    catch(typename myBinaryTree<K, T>::myInvalidKeyword error) {
                        cout << "Узла с таким ключом нет в дереве!\n";
                    }
                case 3:
                    cout << "Введите ключ\n: ";
                    cin >> key;
                    try {
                        element = BinaryTree1->operator[](key);
                        cout << "По ключу \"" << key << "\" храниться \"" << element << "\".\n";
                    }
                    catch(typename myBinaryTree<K, T>::myInvalidKeyword error) {
                        cout << "Узла с таким ключом нет в дереве!\n";
                    }
            }
        }
    }
}

//3
void printBinaryTree(myArraySequence<myBinaryTree<int, int>*> *intArr,
              myArraySequence<myBinaryTree<float, float>*> *floatArr) {
    int type = getType();

    switch (type) {
        default: break;
        case 1:
            printTypeBinaryTree<int, int>(intArr);
            break;
        case 2:
            printTypeBinaryTree<float, float>(floatArr);
            break;
    }
}


template<class K, class T>
void printTypeBinaryTree(myArraySequence<myBinaryTree<K, T>*> *arr) {
    if (arr->length() == 0) {
        cout << "Таких деревьев нет!";
        return;
    }
    int item;
    do {
        cout << "В памяти находится \"" << arr->length() <<
                "\" деревьев этого типа, введите:\n"
                "\t- Индекс элемента для его вывода в консоль\n"
                "\t- Число, больше чем количество деревьев для вывода всех"
                " деревьев этого типа\n"
                "\t- Число меньше нуля для выхода из функции\n:";
        item = getInt();

        if (item < 0) break;

        cout << "В каком формате необходимо вывести \"" << item << "\" дерево:\n"
                "\t0: выбрать другое дерево\n"
                "\t1: в формате произвольной строки\n"
                "\t2: в виде дерева\n: ";

        int item1 = getInt(0, 2);

        if (item1 == 0)
            continue;

        if (item1 == 2) {
            cout << arr->get(item)->strLikeList() << endl;
            continue;
        }

        cout << "Введите строку в формате: ...\"L\"...\"K\"...\"R\". "
                "(например {L}(K)[R], буквы можно менять местами)\n";

        string strFormat, strType;
        cin >> strFormat;

        cout << "Введите буквы \"K\" и \"D\" для вывода в строке ключа и значения соответственно"
                "(можно обе буквы)\n";

        cin >> strType;

        cout << "\"" << item << "\" дерево:\n";

        cout << arr->get(item)->getStr(strFormat, strType) << endl;

    } while (item >= 0);
}

//4
void deleteBinaryTree(myArraySequence<myBinaryTree<int, int>*> *intArr,
               myArraySequence<myBinaryTree<float, float>*> *floatArr) {

    auto item = getType();
    if (item == 0) return;

    switch (item) {
        case 1: deleteTypeBinaryTree(intArr); break;
        case 2: deleteTypeBinaryTree(floatArr); break;
        default: break;
    }
}

template<class K, class T>
void deleteTypeBinaryTree(myArraySequence<myBinaryTree<K, T>*> *arr) {
    if (arr->length() == 0) {
        cout << "Таких деревьев нет!\n";
        return;
    }
    int item;

    while(true) {
        int len = arr->length();
        if (len == 0) {
            cout << "Больше не осталось деревьев этого типа! Автоматический выход из функции\n";
            break;
        }
        cout << "В памяти находится \"" << len << "\" деревьев, введите:\n"
                                                  "\t- Число меньше нуля для выхода из функции\n"
                                                  "\t- Индекс элемента, для его выбора\n"
                                                  "\t- Число, больше длины массива, для вывода деревьев в консоль\n: ";

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

        cout << "Введите номер дерева, с которым надо поменять \""
             << item << "\" дерево\n: ";

        item2 = getInt(0, len - 1);
        if (item != item2) {
            myBinaryTree<K, T> *BinaryTree = arr->get(item);
            arr->set(arr->get(item2), item);
            arr->set(BinaryTree, item2);
        }
    }
}

//5
void testFuncBinaryTree() {
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
        testFuncBinaryTree();
}

#define funcTemplate(T, K) \
template void readTypeBinaryTree(myArraySequence<myBinaryTree<K, T>*> *arr, int count);                    \
template void generateRandomBinaryTree(myArraySequence<myBinaryTree<K, T>*> *arr, int count, K (*funcK)(), T (*funcT)()); \
template void printTypeBinaryTree(myArraySequence<myBinaryTree<K, T>*> *arr);                              \
template void printArr(myArraySequence<myBinaryTree<K, T>*> *arr);                                  \
template void deleteTypeBinaryTree(myArraySequence<myBinaryTree<K, T>*> *arr);                             \
template void operationTypeWithBinaryTree(myArraySequence<myBinaryTree<K, T>*> *arr);                      \


funcTemplate(int, int)

funcTemplate(float, float)

/*
template void readTypeBinaryTree<int, int>(myArraySequence<myBinaryTree<int, int>*> *arr, int count);
template void readTypeBinaryTree<float, float>(myArraySequence<myBinaryTree<float, float>*> *arr, int count);
template void readTypeBinaryTree<complex<int, int>>(myArraySequence<myBinaryTree<complex<int, int>>*> *arr, int count);

template void printTypeBinaryTree<int, int>(myArraySequence<myBinaryTree<int, int>*> *arr);
template void printTypeBinaryTree<float, float>(myArraySequence<myBinaryTree<float, float>*> *arr);
template void printTypeBinaryTree<complex<int, int>>(myArraySequence<myBinaryTree<complex<int, int>>*> *arr);

template void printArr<int, int>(myArraySequence<myBinaryTree<int, int>*> *arr);
 */