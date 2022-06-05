//
// Created by Grisha on 28.05.2021.
//

#include "funcForMenu.h"

int getInt() {
    int k;
    std::cin >> k;
    return k;
}

int getInt(int up) {
    int k;
    std::cin >> k;
    if (k > up) {
        std::cout << "Число вне диапозона. Повторите попытку\n";
        return getInt(up);
    }
    return k;
}

int getInt(int down, int up) {
    int k;
    std::cin >> k;
    if (k > up || k < down) {
        std::cout << "Число вне диапозона. Повторите попытку\n";
        return getInt(down, up);
    }
    return k;
}

int randomInt() {
    return rand()%maxInt;
}

float randomFloat() {
    return (float)randomInt() + (float)randomInt()/(float)randomInt();
}

int getType() {
    std::cout << "Введите число для работы со следующим типом данных:\n"
         << "\t1: int\n"
         << "\t2: float\n"
         << "\t0: Выйти из функции\n"
         << ": ";
    return getInt(0, 2);
}