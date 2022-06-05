//
// Created by Grisha on 24.05.2021.
//

#include "test.h"
#include "iostream"
#include "random"

#define maxTreeSize 1000
#define maxSetSize 1000
#define maxElem 10000

int getRandomInt(int end) {
    return (int) random() % end;
}

int getRandomInt(int start, int end) {
    return (int) random()%(end - start) + start;
}

int Mult(int val) {
    return val * 3;
}

int Summ(int val1, int val2) {
    return val1 + val2;
}

void debugPrint(int count, int passed) {
    std::cout << "\tПройдено " << passed << "/" << count << " тестов. ";
    if (count == passed)
        std::cout << "Тест пройден!\n\n";
    else
        std::cout << "Тест не пройден!\n\n";
}

void test(int count, int debug) {
    testTree(count, debug);
    testSet(count, debug);
}

void testTree(int count, int debug) {
    if (debug)
        std::cout << "Тестирование функций бинарного дерева:\n";

    testTreeInsert(count, debug);
    testCompare(count, debug);
    testTreeDelete(count, debug);
    testTreeFind(count, debug);
    testTreeMap(count, debug);
    testTreeReduce(count, debug);
    testTreeFindSub(count, debug);
}

void testTreeInsert(int count, int debug) {
    int passed = 0, i;
    if (debug)
        std::cout << "\tТестирование добавления в дерево:\n";

    myBinaryTree<int, int> binaryTree;

    for (i = 0; i < count/2; i++) {
        binaryTree.insert(i, i*3);
        if (binaryTree.inTree(i))
            passed++;
    }
    int max = i-1;
    for (; i < count; i++) {
        int key = getRandomInt(max);
        if (binaryTree.inTree(key))
            passed++;
    }
    if (debug)
        debugPrint(count, passed);
}

void testCompare(int count, int debug) {
    int passed = 0, maxSize = maxTreeSize;
    if (debug)
        std::cout << "\tТестирование сравнение деревьев:\n";

    for (int i = 0; i < count; i++) {
        myBinaryTree<int, int> tree1, tree2;
        for (int j = 0; j < maxSize; j++) {
            tree1.insert(j, j * 10);
            tree2.insert(j, j * 10);
        }
        if (tree1 != tree2 || tree1 != tree1 || tree2 != tree2)
            continue;

        tree1.insert(-5, i);
        tree2.insert(-10, i*2);
        if (tree1 == tree2)
            continue;

        passed++;
    }

    if (debug)
        debugPrint(count, passed);
}

void testTreeDelete(int count, int debug) {
    int passed = 0;
    if (debug)
        std::cout << "\tТестирование удаления из дерева:\n";
    
    myBinaryTree<int, int> binaryTree;
    
    for (int i = 0; i < count/2; i++) {
        binaryTree.insert(i, i*2);
    }
    
    for (int i = 0; i < count/2; i++) {
        try {
            binaryTree.remove(i);
            passed++;
        }
        catch (myBinaryTree<int, int>::myInvalidKeyword error){}

        try {
            binaryTree.remove(i);
        }
        catch (myBinaryTree<int, int>::myInvalidKeyword error) {
            passed++;
        }
    }

    if (count % 2 == 1) {
        try {
            binaryTree.remove(8);
        }
        catch (myBinaryTree<int, int>::myInvalidKeyword error) {
            passed++;
        }
    }

    debugPrint(count, passed);
}

void testTreeFind(int count, int debug) {
    int passed = 0, i, k = 3;
    if (debug)
        std::cout << "\tТестирование поиска элемента в дереве:\n";
    myBinaryTree<int, int> binaryTree;
    for (i = 0; i < count/2; i++) {
        binaryTree.insert(i, i*k);
        if (binaryTree[i] == i*k)
            passed++;
    }
    int max = count / 2;

    for (; i < count; i++) {
        int index = getRandomInt(max);
        if (binaryTree[index] == index*k)
            passed++;
    }
    if (debug)
        debugPrint(count, passed);
}

void testTreeMap(int count, int debug) {
    int passed = 0, maxSize = maxTreeSize;
    if (debug)
        std::cout << "\tТестирование функции map:\n";
    for (int i = 0; i < count; i++) {
        myBinaryTree<int, int> binaryTree;
        for (int j = 0; j < maxSize; j++) {
            binaryTree.insert(j, j);
        }
        binaryTree.map(Mult);

        int correct = 1;
        for (int j = 0; j < maxSize && correct; j++) {
            if (binaryTree[j] != j*3)
                correct = 0;
        }
        if (correct)
            passed++;
    }
    if (debug)
        debugPrint(count, passed);
}

void testTreeReduce(int count, int debug) {
    int passed = 0, maxSize = maxTreeSize, maxVal = maxElem;
    if (debug)
        std::cout << "\tТестирование функции reduce:\n";
    for (int i = 0; i < count; i++) {
        myBinaryTree<int, int> binaryTree;
        int sum = 0;
        for (int j = 0; j < maxSize; j++) {
            int val = getRandomInt(maxVal);
            sum += val;
            binaryTree.insert(j, val);
        }

        int res = binaryTree.reduce(Summ, 0);
        if (sum == res)
            passed++;
    }
    if (debug)
        debugPrint(count, passed);
}

void testTreeFindSub(int count, int debug) {
    int passed = 0, maxSize = maxTreeSize, maxVal = maxElem;
    if (debug)
        std::cout << "\tТестирование поиска поддерева:\n";
    for (int i = 0; i < count; i++) {
        myBinaryTree<int, int> binaryTree;
        for (int j = 0; j < maxSize; j++) {
            binaryTree.insert(j, getRandomInt(maxVal));
        }

        auto *subTree = binaryTree.getSubTree(getRandomInt(maxSize));

        if (!binaryTree.inTree(*subTree)) {
            delete subTree;
            continue;
        }

        auto *keys = subTree->getKeys();
        if (keys->length() == 0) {
            passed++;
            delete keys;
            delete subTree;
            continue;
        }

        int index = getRandomInt(keys->length());
        subTree->operator[](keys->operator[](index)) += 1;

        if (!binaryTree.inTree(*subTree))
            passed++;

        delete keys;
        delete subTree;
    }

    if (debug)
        debugPrint(count, passed);
}


void testSet(int count, int debug) {
    if (debug)
        std::cout << "Тестирование функций множества:\n";

    testAddElem(count, debug);
    testDeleteElem(count, debug);
    testFindElem(count, debug);
    testFindSet(count, debug);

    testJoin(count, debug);
    testCross(count, debug);
    testSub(count, debug);
    testXor(count, debug);
}

void testAddElem(int count, int debug) {
    int passed = 0, maxSize = maxSetSize, maxVal = maxElem;
    if (debug)
        std::cout << "\tТестирование добавления элементов:\n";
    for (int i = 0; i < count; i++) {
        mySet<int> set1, set2;
        for (int j = 0; j < maxSize; j++) {
            int val = getRandomInt(maxElem);
            set1.add(val);
            if (getRandomInt(2))
                set2.add(val);
        }
        if (!(set1 >= set2))
            continue;

        set2.add(maxVal + 1);
        if (!(set1 >= set2))
            passed++;
    }
    if (debug)
        debugPrint(count, passed);
}

void testDeleteElem(int count, int debug) {
    int passed = 0, maxSize = maxSetSize, maxVal = maxElem;
    if (debug)
        std::cout << "\tТестирование удаления элементов:\n";
    for (int i = 0; i < count; i++) {
        mySet<int> set1, set2;
        for (int j = 0; j < maxSize; j++) {
            int val = getRandomInt(maxElem);
            set1.add(val);
        }
        set2 = set1;

        int arrElem[] = {maxElem + 1, maxElem + 2, maxElem + 3};

        for (auto j : arrElem)
            set2.add(j);

        int correct = 1;
        for (auto j : arrElem) {
            if (set1 == set2) {
                correct = 0;
                break;
            }
            set2.remove(j);
        }
        if (correct && set1 == set2)
            passed++;
    }
    if (debug)
        debugPrint(count, passed);
}

void testFindElem(int count, int debug) {
    int passed = 0, maxSize = maxSetSize, findCount = 100;
    if (debug)
        std::cout << "\tТестирование поиска элемента:\n";
    for (int i = 0; i < count; i++) {
        mySet<int> set;
        for (int j = 0; j < maxSize; j++) {
            set.add(j);
        }

        int correct = 1;
        for (int j = 0; j < findCount && correct; j++) {
            if (!set.find(getRandomInt(maxSize)))
                correct = 0;
        }
        if (correct)
            passed++;
    }
    if (debug)
        debugPrint(count, passed);
}

void testFindSet(int count, int debug) {
    int passed = 0, maxSize = maxSetSize, maxVal = maxElem;
    if (debug)
        std::cout << "\tТестирование поиска подмножества:\n";
    for (int i = 0; i < count; i++) {
        mySet<int> set1, set2;
        for (int j = 0; j < maxSize; j++) {
            int val = getRandomInt(maxVal);
            set1.add(val);
            if (getRandomInt(2))
                set2.add(val);
        }
        if (set1 < set2)
            continue;

        set2.add(maxVal + 1);
        if (set1 >= set2)
            continue;

        passed++;
    }
    if (debug)
        debugPrint(count, passed);
}

void testJoin(int count, int debug) {
    int passed = 0, maxSize = maxSetSize,maxVal = maxElem;
    if (debug)
        std::cout << "\tТестирование объединения множеств:\n";
    for (int i = 0; i < count; i++) {
        mySet<int> set1, set2;
        for (int j = 0; j < maxSize; j++) {
            set1.add(getRandomInt(maxVal));
            set2.add(getRandomInt(maxVal));
        }

        auto set3 = set1 + set2;

        if (set3 != set2 + set1)
            continue;

        if (set3 >= set1 && set3 >= set2)
            passed++;
    }
    if (debug)
        debugPrint(count, passed);
}

void testCross(int count, int debug) {
    int passed = 0, maxSize = maxSetSize, maxVal = maxElem;
    if (debug)
        std::cout << "\tТестирование пересечения множеств:\n";
    for (int i = 0; i < count; i++) {
        mySet<int> set1, set2;
        for (int j = 0; j < count; j++) {
            set1.add(getRandomInt(maxVal));
            set2.add(getRandomInt(maxVal));
        }

        auto set3 = set1 * set2;

        if (set3 != set2 * set1)
            continue;

        if (set3 <= set1 && set3 <= set2)
            passed++;
    }
    if (debug)
        debugPrint(count, passed);
}

void testSub(int count, int debug) {
    int passed = 0, maxSize = maxSetSize, maxVal = maxElem;
    if (debug)
        std::cout << "\tТестирование вычитания множеств:\n";
    for (int i = 0; i < count; i++) {
        mySet<int> set1, set2;
        for (int j = 0; j < count; j++) {
            set1.add(getRandomInt(maxVal));
            set2.add(getRandomInt(maxVal));
        }

        auto set3 = set1 - set2;

        if (set3 <= set1 && (set3 * set2).length() == 0)
            passed++;
    }
    if (debug)
        debugPrint(count, passed);
}

void testXor(int count, int debug) {
    int passed = 0, maxSize = maxSetSize, maxVal = maxElem;
    if (debug)
        std::cout << "\tТестирование Жигалкинского сложения множеств:\n";
    for (int i = 0; i < count; i++) {
        mySet<int> set1, set2;
        for (int j = 0; j < count; j++) {
            set1.add(getRandomInt(maxVal));
            set2.add(getRandomInt(maxVal));
        }

        auto set3 = set1 xor set2;

        if (set3 != (set2 xor set1))
            continue;

        if (set3 == (set1 - set2) + (set2 - set1))
            passed++;
    }
    if (debug)
        debugPrint(count, passed);
}