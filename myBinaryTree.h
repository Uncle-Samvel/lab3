//
// Created by Grisha on 23.04.2021.
//

#ifndef LAB3_MYBINARYTREE_H
#define LAB3_MYBINARYTREE_H

#include "myStack.h"
#include "myQueue.h"
#include "myArraySequence.h"

#include <iostream>

template <class Key, class Data>
class myBinaryTree {
public:
    using K = Key;
    using T = Data;
    using typeHeight = int;

    template<class K, class T>
    class myNode {  //Класс узла дерева
    public:
        K key;                       //ключ узла
        T data;                      //данные узла
        typeHeight height = 1;       //высота узла (для балансировки)

        myNode *left = nullptr;      //укакзатель на левый узел
        myNode *right = nullptr;     //указатель на правый узел

        myNode(K key1, T data1): key(key1), data(data1) {}  //конструктор

        myNode& operator = (const myNode& br) {             //операция присваивания
            key = br.key;
            data = br.key;
            height = br.height;

            left = br.left;
            right = br.right;

            return *this;
        }

        typeHeight getHeightDelta() {                      //функция для нахождения разности высот (для балансировки)
            auto h1 = left == nullptr ? 0 : left->height;
            auto h2 = right == nullptr ? 0 : right->height;
            return h2 - h1;
        }

        void updateHeight() {                              //функция обновления высоты (для балансировки)
            auto h1 = left == nullptr ? 0 : left->height;
            auto h2 = right == nullptr ? 0 : right->height;
            height = (h1 > h2 ? h1 : h2) + 1;
        }

        myNode* rotateLeft() {                             //малый левый поворот (для балансировки)
            myNode *res = right;
            right = res->left;
            res->left = this;
            updateHeight();
            res->updateHeight();

            return res;
        }

        myNode* rotateRight() {                            //малый правый поворот (для балансировки)
            myNode *res = left;
            left = res->right;
            res->right = this;
            updateHeight();
            res->updateHeight();

            return res;
        }

        myNode* balance() {                                //функция балансировки узла (для балансировки, очевидно)
            updateHeight();                                //возращает узел, который должен стоять на месте исходного
            auto delta = getHeightDelta();                 //TODO лучше бы переделать, чтоб было красивее
            if (delta < -1) {
                if (left != nullptr && left->getHeightDelta() > 0)
                    left = left->rotateLeft();
                return rotateRight();
            }
            if (delta > 1) {
                if (right != nullptr && right->getHeightDelta() < 0)
                    right = right->rotateRight();
                return rotateLeft();
            }
            return this;
        }
    };

    class myInvalidKeyword{                               //класс ошибки ключа (такого ключа нет в дереве)
    public:
        K key;
        explicit myInvalidKeyword(K key): key(key) {}
    };

    class myIsEmpty{};                                    //класс ошибки пустоты (пустое дерево)

    template<class K, class T>
    class myIterator {                                    //класс итератора (полный п**дец)
    private:
        myBinaryTree<K, T> *binaryTree = nullptr;
        myStack<myNode<K, T>*> *stack = nullptr;
        myNode<K, T> *now = nullptr;
    public:
        myIterator(): stack(new myStack<myNode<K, T>*>) {}

        myIterator(myBinaryTree<K, T> *tree) {
            binaryTree = tree;
            stack = new myStack<myNode<K, T>*>;
        }

        myIterator(myBinaryTree<K, T> *tree, myStack<myNode<K, T>*>* Stack, myNode<K, T> *elem) {
            binaryTree = tree;
            stack = new myStack<myNode<K, T>*>(Stack);
            now = elem;
        }

        myIterator(const myIterator<K, T>& iter) {
            binaryTree = iter.binaryTree;
            stack = new myStack<myNode<K, T>*>(iter.stack);
            now = iter.now;
        }

        ~myIterator() {
            if (stack)
                delete stack;
        }


        myIterator<K, T>& begin() {
            now = binaryTree->head;
            if (now == nullptr)
                return *this;

            stack->add(nullptr);

            while(now->left != nullptr) {
                stack->add(now);
                now = now->left;
            }
            return *this;
        }

        myIterator<K, T> end() {
            return myIterator<K, T>(binaryTree, new myStack<myNode<K, T>*>, nullptr);
        }

        myIterator<K, T>& operator++() {
            if (now == nullptr)
                return *this;

            if (now->right != nullptr) {
                now = now->right;
                while (now->left != nullptr) {
                    stack->add(now);
                    now = now->left;
                }
            }
            else {
                now = stack->get();
            }

            return *this;
        }

        int operator == (myIterator<K, T>& iter) {
            return binaryTree->operator==(*iter.binaryTree) &&
                   now == iter.now &&
                   stack->length() == iter.stack->length();
        }

        int operator != (myIterator<K, T>& iter) {
            return !(operator==(iter));
        }

        T& operator *() {
            return now->data;
        }
    };
    /**/
private:
    myNode<K, T> *head;             //указатель на вершину (начало) дерева
    short int _isCopy_ = 0;         //переменная, говорящая о том, является ли дерево копией (нужно для деконструктора)

    ///Функции для работы преобразования в строку

    std::string strFromQueue(int* queue, int num, const std::string &Start, const std::string &First,
                             const std::string &Second, const std::string &End, const std::string &typePrint) const {
        int ind1 = 0, ind2 = 0;     //функция, которая получает строку для узла
        switch (queue[num]) {
            default: return std::string();
            case 0:
                return myBinaryTree<K, T>(head->left).strSplit(queue, Start, First, Second, End, typePrint);

            case 1:
                ind1 = (int) typePrint.find('K');
                ind2 = (int) typePrint.find('D');

                if (ind1 > typePrint.length() && ind2 > typePrint.length())
                    return std::string();

                if (ind1 > typePrint.length())
                    return std::to_string(head->data);

                if (ind2 > typePrint.length())
                    return std::to_string(head->key);

                if (ind1 <= typePrint.length() && ind2 <= typePrint.length())
                    return std::string("\"") + std::to_string(head->key) + ", " + std::to_string(head->data) + "\"";

            case 2:
                return myBinaryTree<K, T>(head->right).strSplit(queue, Start, First, Second, End, typePrint);
        }
        return std::string();
    }

    std::string strSplit(int* queue, const std::string &Start, const std::string &First,
                         const std::string &Second, const std::string &End, const std::string &typePrint) const {
        if (head == nullptr) {      //функция, которая создаёт строку для дерева (рекурсивно)
            return std::string();
        }

        std::string res = Start;
        res += strFromQueue(queue, 0, Start, First, Second, End, typePrint);
        res += First;
        res += strFromQueue(queue, 1, Start, First, Second, End, typePrint);
        res += Second;
        res += strFromQueue(queue, 2, Start, First, Second, End, typePrint);
        res += End;

        return res;
    }

    void strGetKeys(const std::string &str, int* queue, int* key, std::string* keys,
                    std::string &Start, std::string &First, std::string &Second, std::string &End) const {
        key[0] = (int) str.find(keys[0]);  //функция, которая определяет правило обхода (порядок букв ЛКП)
        key[1] = (int) str.find(keys[1]);  //и разделяет исходную строку
        key[2] = (int) str.find(keys[2]);

        if (key[0] > str.length() || key[1] > str.length() || key[2] > str.length())
            return;

        if (key[0] < key[1] && key[1] < key[2]) {
            queue[0] = 0; queue[1] = 1; queue[2] = 2;
        }
        else if (key[0] < key[2] && key[2] < key[1]) {
            queue[0] = 0; queue[1] = 2; queue[2] = 1;
            int swap = key[1]; key[1] = key[2]; key[2] = swap;
        }
        else if (key[1] < key[0] && key[0] < key[2]) {
            queue[0] = 1; queue[1] = 0; queue[2] = 2;
            int swap = key[0]; key[0] = key[1]; key[1] = swap;
        }
        else if (key[1] < key[2] && key[2] < key[0]) {
            queue[0] = 1; queue[1] = 2; queue[2] = 0;
            int swap = key[0]; key[0] = key[1]; key[1] = key[2]; key[2] = swap;
        }
        else if (key[2] < key[0] && key[0] < key[1]) {
            queue[0] = 2; queue[1] = 0; queue[2] = 1;
            int swap = key[0]; key[0] = key[2]; key[2] = key[1]; key[1] = swap;
        }
        else if (key[2] < key[1] && key[1] < key[0]){
            queue[0] = 2; queue[1] = 1; queue[2] = 0;
            int swap = key[0]; key[0] = key[2]; key[2] = swap;
        }

        Start  = str.substr(0, key[0]);
        First  = str.substr(key[0] + keys[queue[0]].length(), key[1] - key[0] - keys[queue[0]].length());
        Second = str.substr(key[1] + keys[queue[1]].length(), key[2] - key[1] - keys[queue[1]].length());
        End    = str.substr(key[2] + keys[queue[2]].length(), str.length() - key[2] - keys[queue[2]].length());
    }

    ///Функции для работы получение ключей и значений в дереве

    myArraySequence<T>* getValues(myNode<K, T>* node) const {  //рекурсивная функция, которая извлекает все значения дерева
        if (!node) {
            return new myArraySequence<T>;
        }

        myArraySequence<T>* res1 = getValues(node->left);
        myArraySequence<T>* res2 = getValues(node->right);

        res1->append(node->data);
        res1->concat(res2);

        delete res2;
        return res1;
    }

    myArraySequence<K>* getKeys(myNode<K, T>* node) const {  //рекурсивная функция, которая извлекает все ключи дерева
        if (!node) {
            return new myArraySequence<K>;
        }

        myArraySequence<K>* res1 = getKeys(node->left);
        myArraySequence<K>* res2 = getKeys(node->right);

        res1->append(node->key);
        res1->concat(res2);

        delete res2;
        return res1;
    }

    ///Функция для поиска поддерева

    int isSubTree(myNode<K, T> *tree, myNode<K, T> *subTree) {  //рекурсивная функция для поиска поддерева
        if (tree == subTree)
            return 1;

        if (subTree == nullptr)
            return 1;

        if (tree == nullptr)
            return 0;

        if (tree->key != subTree->key || tree->data != subTree->data)
            return 0;

        if (!isSubTree(tree->left, subTree->left))
            return 0;

        if (!isSubTree(tree->right, subTree->right))
            return 0;

        return 1;
    }

    ///Функция для поиска узла по ключу

    myNode<K, T>* findNode(K key) {  //нерекурсивная функция поиска узла по ключу (nullptr, если такого ключа нет)
        myNode<K, T> *res = head;
        while (head != nullptr) {
            if (res->key == key) {
                break;
            }
            else if (res->key < key) {
                res = res->left;
            }
            else {
                res = res->right;
            }
        }

        return res;
    }

public:
    myBinaryTree(): head(nullptr) {}  //конструктор

    explicit myBinaryTree(myNode<K, T> *element): head(element), _isCopy_(1) {}  //конструктор

    void Delete() {  //рекурсивная функция удаления
        if (head == nullptr)
            return;

        if (head->left != nullptr) {
            myBinaryTree<K, T>(head->left).Delete();  //создаёт копию дерева из левого узла и удаляет его (рекурсивно)
        }
        if (head->right != nullptr) {
            myBinaryTree<K, T>(head->right).Delete(); //создаёт копию дерева из правого узла и удаляет его (рекурсивно)
        }
        delete head;
        head = nullptr;
    }

    myBinaryTree(const K& key, const T& data) {  //конструктор
        auto *res = new myNode<K, T>;
        res->key = key;
        res->data = data;
        head = res;
    }

    myBinaryTree(const myArraySequence<K>& keys, const myArraySequence<T>& elements) {  //конструктор
        auto len1 = keys.length(), len2 = elements.length();
        head = nullptr;
        auto min = len1 > len2 ? len2 : len1;

        for (int i = 0; i < min; i++) {
            K key = keys.get(i);
            T element = elements.get(i);
            insert(key, element);
        }
    }
    

    ~myBinaryTree() {  //деструктор
        if (!_isCopy_) //не происходит удаления, если дерево является копией (будет п**да исходному)
            Delete();
    }


    T find(K key) const {  //функция поиска значения по ключу (через поиск узла по ключу)
        myNode<K, T> *res = findNode(key);
        if (res == nullptr) {
            throw myInvalidKeyword();
        }

        return res->data;
    }

    myBinaryTree<K, T>* insert(K key, T data) {  //функция вставки пары ключ/значение
        if (head == nullptr) {                   //вставка в самое начало, если дерево пустое
            head = new myNode<K, T>(key, data);
            return this;
        }

        if (key == head->key) {                  //замена значения по ключу, если такой ключ нашёлся
            head->data = data;
            return this;
        }

        if (key < head->key) {
            head->left = myBinaryTree<K, T>(head->left).insert(key, data)->head; //рекурсивное добаление в левое поддерево
        }
        else {
            head->right = myBinaryTree<K, T>(head->right).insert(key, data)->head; //рекурсивное добавление в правое поддерево
        }

        /*
         * добавление произойдёт только тогда, когда при рекурсивном добавлении создастся пустое дерево (дерево с
         * nullptr вершиной, такое возможно только тогда, когда у предка поле left или right == nullptr).
         * соответственно создастся новая вершина (первое условие этой функции), но чтобы эту вершину привязать к дереву
         * (у меня не храниться ссылка на предка), надо вернуть эту вершину и записать её в соответственное поле
         * поэтому когда мы вызываем функцию рекурсивно для левого поддерева, мы обновляем его (вдруг в него что-то добавиться)
         *
         * "левый узел"  = "поддерево, образованние из левого  узла"->"начало дерева"
         * "правый узел" = "поддерево, образованние из правого узла"->"начало дерева"
         */

        head->updateHeight();                    //балансировка узла
        int delta = head->getHeightDelta();

        if (delta <= 1 && delta >= -1) {
//            head->height = maxVal + 1;
            return this;
        }
        head = head->balance();

        return this;
    }

    myBinaryTree<K, T>* remove(K key) {  //удаление пары ключ/значение (по ключу, рекурсивно)
        if (head == nullptr) throw myInvalidKeyword(key);   //рекурсивно пришли в пустое поддерева -> ключ не найден

        if (key != head->key) {   //рекурсивный вызов функции для левого или правого поддерева
            if (key < head->key)
                head->left = myBinaryTree<K, T>(head->left).remove(key)->head;  //та же замена узлов, что и в добавлении
            else
                head->right = myBinaryTree<K, T>(head->right).remove(key)->head;
            head = head->balance();  //балансировка узла, после удаления (или не удаления) пары
            return this;
        }

        if (head->left == nullptr && head->right == nullptr) {  //нашли нужный узел, у которого нет поддеревьев,
            delete head;                                        // обычное удаление
            head = nullptr;
            return this;
        }

        if (head->left == nullptr && head->right != nullptr) {  //нашли нужный узел, у которого есть правый узел
            myNode<K, T> *res = head->right;                    //заменяем начало дерева на правый узел и возвращаем его
            delete head;
            head = res;
            return this;
        }

        if (head->left != nullptr && head->right == nullptr) {  //нашли нужный узел, у которого есть левый узел
            myNode<K, T> *res = head->left;                     //то же самое, что в предыдущем, но для левого
            delete head;
            head = res;
            return this;
        }

        if (head->left != nullptr && head->right != nullptr) {  //нашли нужный узел, у которого есть оба узла
            /*
             * так как дерево балансировочное, то необходимо удалить узел так, чтобы не нарушилась балансировка
             * для этого:
             * 1: ищем узел, у которого высота наибольшая (если одинаковые, то правый)
             * 2: у данного узла:
             *    2.1: если левый,  то ищем самый правый узел (идём только направо, пока не дойдём до nullptr),
             *         запоминая все узлы, которые посетили (складываем в myStack<...> *stack)
             *    2.2: если правый, то ищем самый левый  узел (идём только влево,   пока не дойдём до nullptr),
             *         запоминая все узлы, которые посетили (складываем в myStack<...> *stack)
             *    дальше запоминаем найденный узел, удаляяем его из дерево (условия до этого)
             * 3: вставляем найденный узел на место узла, в котором сейчас находимся (узел с ключом K key)
             * 4: выполняем балансировку для узлов, которые находятся в myStack<...> *stack
             * 5: выполняем балансировку для данного узла дерева и возвращаем его
             */
            auto h1 = head->left->height;
            auto h2 = head->right->height;
            if (h1 > h2) {
                myStack<myNode<K, T>*> stack;
                myNode<K, T> *br, *last = nullptr;
                for (br = head->left; br->right != nullptr; br = br->right) {
                    if (last != nullptr)
                        stack.add(last);
                    last = br;
                }

                if (last == nullptr) {
                    br->right = head->right;
                    delete head;
                    head = br->balance();
                    return this;
                }

                last->right = br->left;
                br->left = head->left->balance();
                br->right = head->right;
                delete head;
                head = br;
                myNode<K, T> *thing = last;

                while (stack.length() != 0) {
                    thing = stack.get();
                    thing->right = last->balance();
                    last = thing;
                }

                head->left = thing->balance();
                head = head->balance();
            }
            else {
                myNode<K, T> *br, *last = nullptr;
                myStack<myNode<K, T>*> stack;
                for (br = head->right; br->left != nullptr; br = br->left) {
                    if (last != nullptr)
                        stack.add(last);
                    last = br;
                }

                if (last == nullptr) {
                    br->left = head->left;
                    delete head;
                    head = br->balance();
                    return this;
                }

                last->left = br->right;
                br->right = head->right->balance();
                br->left = head->left;
                delete head;
                head = br;

                myNode<K, T>* thing = last;
                while(stack.length() != 0) {
                    thing = stack.get();
                    thing->left = last->balance();
                    last = thing;
                }

                head->right = thing->balance();
                head = head->balance();
            }

            return this;
        }

        return this;
    }

    std::string getStr(const std::string& str) const {  //функция получения строки из строки произвольного обхода
        std::string typePrint("KD");
        return getStr(str, typePrint);
    }

    std::string getStr(const std::string& str, const std::string& typePrint) const {
        int queue[] = {-1, -1, -1};                   //функция получения строки из строки произвольного обхода
        int key[3];                                   //с выбором данныйх (ключ, значения, оба вместе)
        int val = str.length() + 1;
        for (auto &i : key) {
            i = val;
        }
        std::string Start, First, Second, End;

        std::string keys[] = {std::string("L"), std::string("K"), std::string("R")};

        strGetKeys(str, queue, key, keys, Start, First, Second, End);

        return strSplit(queue, Start, First, Second, End, typePrint);
    }

    std::string strLikeList() {  //вывод дерева в виде списка (красивый вывод)
        return strLikeList(0, 0);
    }

    std::string strLikeList(int count, int pol) {  //вывод дерева в виде списка с аргументами (красивый вывод)
        std::string res;
        for (int i = 0; i < count - (pol != 0) + count - 1; i++)
            res += ' ';

        if (pol == 1)
            res += "├-";
        else if (pol == 2)
            res += "└-";

        if (head == nullptr) {
            res += "nullptr\n";
            return res;
        }
        res += std::to_string(head->key) + '\n';

        res += myBinaryTree<K, T>(head->left).strLikeList(count + 1, 1);
        res += myBinaryTree<K, T>(head->right).strLikeList(count + 1, 2);
        return res;
    }

    myBinaryTree<K, T>& operator = (const myBinaryTree<K, T>& binaryTree) {  //оператор присваивания
        Delete();
        //toOperatorEqual(binaryTree.head);
        if (binaryTree.head == nullptr)
            return *this;

        myQueue<myNode<K, T>*> queue(binaryTree.head);  //создаём очередь узлов для обхода (начальныйй узел - вершина дерева)
                                                        //так как дерево изначально сбалансировано, элементы добавляются
                                                        //по уровням (вершина, дочерние узлы вершины, их дочерние узлы, и тд)
                                                        //таким образом при добавлении не будет лишний раз вызываться балансировка
        while(queue.length() != 0) {
            auto *nodeRes = queue.get();
            insert(nodeRes->key, nodeRes->data);
            if (nodeRes->left != nullptr)
                queue.add(nodeRes->left);

            if (nodeRes->right != nullptr)
                queue.add(nodeRes->right);
        }

        return *this;
    }

    int equal(const myBinaryTree<K, T>& binaryTree) {  //оператор сравнения деревьев (1, если полностью индентичны)
        if (head == binaryTree.head)
            return 1;

        if (head == nullptr || binaryTree.head == nullptr)
            return 0;

        if (head->key != binaryTree.head->key || head->data != binaryTree.head->data)
            return 0;

        if (!(myBinaryTree<K, T>(head->left).equal(myBinaryTree<K, T>(binaryTree.head->left))))
            return 0;

        if (!(myBinaryTree<K, T>(head->right).equal(myBinaryTree<K, T>(binaryTree.head->right))))
            return 0;

        return 1;
    }

    int operator == (const myBinaryTree<K, T>& binaryTree) {
        return equal(binaryTree);
    }

    int operator != (const myBinaryTree<K, T>& binaryTree) {
        return !equal(binaryTree);
    }

    T& operator [] (K key) {   //как find, но позволяем изменять значение по ключу (возвращает ссылку на значение)
        auto *res = findNode(key);
        if (res == nullptr)
            throw myInvalidKeyword(key);

        return res->data;
    }

    myArraySequence<T>* getValues() const {  //вызвращает массив значений дерева
        return getValues(head);
    }

    myArraySequence<K>* getKeys() const {   //возвращает массив ключей дерева
        return getKeys(head);
    }

    void map(T (*f)()) {  //функция для изменения каждого значения дерева (применяется к каждому элементу дерева)
        if (!head)        //типо "node->data = f();"
            return;

        head->data = f();
        myBinaryTree<K, T>(head->left).map(f);
        myBinaryTree<K, T>(head->right).map(f);
    }

    void map(T (*f)(T value)) { //функция для изменения каждого элемента дерева в зависимости от его исходного значения
        if (!head)              //типо "node->data = f(node->data);"
            return;

        head->data = f(head->data);
        myBinaryTree<K, T>(head->left).map(f);
        myBinaryTree<K, T>(head->right).map(f);
    }

    template<class U>
    U reduce(U (*f)(U res, T value), U start) {  //функция для поэлементного применения к элементам дерева
        if (!head)                               //с накоплением (типо "res = f(f...(f(start, a[0]), a[1])..., a[n])" )
            return start;                        //или "res = f(start, a[0]); res = f(res, a[1]); ...; res = f(res, a[n]);

        auto res = start;

        auto *data = getValues();

        for (int i = 0; i < data->length(); i++) {
            res = f(res, data->get(i));
        }

        return res;
    }

    myBinaryTree<K, T>* getSubTree(K key) {   //функция извлечение поддерева
        auto res = new myBinaryTree<K, T>; //создаём новое дерево
        res->operator=(myBinaryTree<K, T>(findNode(key))); //копируем данные из дерева, созданного от узла с ключом K key (если его нет, то узел == nullptr)
        return res;
    }

    int inTree(K key) {     //функция, проверяющая на вхождение ключа в дерево
        return findNode(key) != nullptr;
    }

    int inTree(const myBinaryTree<K, T>& binaryTree) {  //функция, проверяющая на включение поддерева
        if (binaryTree.head == nullptr)   //пустое дерево всегда поддерево
            return 1;

        auto *node = findNode(binaryTree.head->key);  //поиск узла с нужным ключом

        if (node == binaryTree.head)                  //если адрес узла совпадает с адресом начала дерева
            return 1;                                 //то деревья равны (и искомое дерево являяется поддеревом)

        if (node == nullptr)                          //нет узла с нужным ключом, значи нет искомого поддерева
            return 0;

        return isSubTree(node, binaryTree.head);     //проверка на поддерево
    }

    myBinaryTree<K, T>& getLink() {                  //получение ссылки на дерево (хз зачем, но вроде где-то юзается)
        return *this;
    }
};

template <class K, class T>
std::ostream& operator << (std::ostream& cout, const myBinaryTree<K, T> &binaryTree) {  //переопределение cout <<
    std::string format("{L}[K](R)");
    return std::cout << binaryTree.getStr(format, std::string("K"));
}

#endif //LAB3_MYBINARYTREE_H
