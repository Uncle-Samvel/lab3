//
// Created by Grisha on 28.05.2021.
//

#ifndef LAB3_MENUTREE_H
#define LAB3_MENUTREE_H

#include <complex>
#include <iostream>
#include "tests/test.h"
#include "Headers/mySet.h"
#include "funcForMenu.h"

void mainMenuBinaryTree();

//1
void readBinaryTree(myArraySequence<myBinaryTree<int, int>*> *intArr,
                    myArraySequence<myBinaryTree<float, float>*> *floatArr);

template<class K, class T>
void readTypeBinaryTree(myArraySequence<myBinaryTree<K, T>*> *arr, int count);

template<class K, class T>
void generateRandomBinaryTree(myArraySequence<myBinaryTree<K, T>*> *arr, int count, K (*funcK)(), T (*funcT)());

//2
void operationWithBinaryTree(myArraySequence<myBinaryTree<int, int>*> *intArr,
                             myArraySequence<myBinaryTree<float, float>*> *floatArr);

template<class K, class T>
void operationTypeWithBinaryTree(myArraySequence<myBinaryTree<K, T>*> *arr);

//3
void printBinaryTree(myArraySequence<myBinaryTree<int, int>*> *intArr,
                     myArraySequence<myBinaryTree<float, float>*> *floatArr);

template<class K, class T>
void printTypeBinaryTree(myArraySequence<myBinaryTree<K, T>*> *arr);


//4
void deleteBinaryTree(myArraySequence<myBinaryTree<int, int>*> *intArr,
                      myArraySequence<myBinaryTree<float, float>*> *floatArr);

template<class K, class T>
void deleteTypeBinaryTree(myArraySequence<myBinaryTree<K, T>*> *arr);

//5
void testFuncBinaryTree();

#endif //LAB3_MENUTREE_H
