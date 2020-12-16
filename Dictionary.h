#ifndef P3_SEARCH_DICTIONARY_H
#define P3_SEARCH_DICTIONARY_H

#define RED true
#define BLACK false

template<typename K, typename V>
class RBNode {
public:
    K key;
    V value;
    bool color = RED;
    RBNode<K, V>* parent = nullptr;
    RBNode<K, V>* leftChild = nullptr;
    RBNode<K, V>* rightChild = nullptr;

    RBNode() {

    }

    RBNode(K key_, V value_) {
        key = key_;
        value = value_;
    }

    RBNode<K, V>* grandparent() {
        if (parent != nullptr)
            return parent->parent;
        else
            return nullptr;
    }

    RBNode<K, V>* uncle() {
        RBNode<K, V>* grand = grandparent();
        if (grand == nullptr)
            return grand;
        else {
            if (parent == grand->leftChild) {
                return grand->rightChild;
            } else {
                return grand->leftChild;
            }
        }
    }
};

// Можно считать, что тип K является упорядоченным и предоставляет
// правильную перегрузку operator<() и operator==().
template<typename K, typename V>
class Dictionary final {
private:
    RBNode<K, V>* root_ = nullptr;

//    RBNode<K, V> treeNull;
//
    RBNode<K, V>* initializeTreeNullForRemove(RBNode<K, V>* parent) {
        RBNode<K, V>* node = new RBNode<K, V>;
//        node->key = new K();
//        node->value = new V();
        node->parent = parent;
//        node->leftChild = nullptr;
//        node->rightChild = nullptr;
        node->color = BLACK;
        parent->rightChild = node;
        return node;
    }

    int size_ = 0;

    void rotateLeftRBT(RBNode<K, V>* node) {
        RBNode<K, V>* nodeRightChild = node->rightChild; // right child exists since we want to rotate left
        RBNode<K, V>* childLeftChild = nodeRightChild->leftChild; // may be nullptr
        RBNode<K, V>* formerParent = node->parent; // former parent

        node->rightChild = childLeftChild;
        if (childLeftChild != nullptr)
            childLeftChild->parent = node;

        if (node->parent == nullptr) { // node is a root
            root_ = nodeRightChild;
        }

        nodeRightChild->parent = formerParent;
        nodeRightChild->leftChild = node;
        node->parent = nodeRightChild;

        if (formerParent != nullptr) {
            if (formerParent->leftChild == node)
                formerParent->leftChild = nodeRightChild;
            else
                formerParent->rightChild = nodeRightChild;
        }
    }

    void rotateRightRBT(RBNode<K, V>* node) {
        RBNode<K, V>* nodeLeftChild = node->leftChild; // not nullptr
        RBNode<K, V>* childRightChild = nodeLeftChild->rightChild; // may be nullptr
        RBNode<K, V>* grandParent = nodeLeftChild->grandparent();

        node->leftChild = childRightChild;
        if (childRightChild != nullptr)
            childRightChild->parent = node;

        if (node->parent == nullptr) { // node is a root
            root_ = nodeLeftChild;
        }

        nodeLeftChild->parent = node->parent;
        nodeLeftChild->rightChild = node;
        node->parent = nodeLeftChild;

        if (grandParent != nullptr) {
            if (grandParent->leftChild == node) {
                grandParent->leftChild = nodeLeftChild;
            } else {
                grandParent->rightChild = nodeLeftChild;
            }
        }
    }

    void insertFixup(RBNode<K, V>* node) {
        if (node == root_) {
            node->color = BLACK;
            return;
        }

        RBNode<K, V>* parent = node->parent;
        RBNode<K, V>* uncle = node->uncle();
        RBNode<K, V>* grandparent = node->grandparent();

        if (parent->color == BLACK) {
            return;
        }

        if (uncle != nullptr) { // parent & uncle are red - change colors
            if (uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                insertFixup(grandparent);
            } else {
                // parent is red, uncle is black or absent
                if (grandparent->leftChild == parent) { // if parent - left child
                    if (parent->leftChild == node) { // if node - left child
                        parent->color = BLACK;
                        grandparent->color = RED;
                        rotateRightRBT(grandparent);
                    } else { // if node - right child
                        rotateLeftRBT(parent);
                        node->color = BLACK;
                        grandparent->color = RED;
                        rotateRightRBT(grandparent);
                    }
                } else { // if parent - right child
                    if (parent->rightChild == node) { // if node - right child
                        parent->color = BLACK;
                        grandparent->color = RED;
                        rotateLeftRBT(grandparent);
                    } else { // if node - left child
                        rotateRightRBT(parent);
                        node->color = BLACK;
                        grandparent->color = RED;
                        rotateLeftRBT(grandparent);
                    }
                }
            }
        } else {
            // parent is red, uncle is black or absent
            if (grandparent->leftChild == parent) { // if parent - left child
                if (parent->leftChild == node) { // if node - left child
                    parent->color = BLACK;
                    grandparent->color = RED;
                    rotateRightRBT(grandparent);
                } else { // if node - right child
                    rotateLeftRBT(parent);
                    node->color = BLACK;
                    grandparent->color = RED;
                    rotateRightRBT(grandparent);
                }
            } else { // if parent - right child
                if (parent->rightChild == node) { // if node - right child
                    parent->color = BLACK;
                    grandparent->color = RED;
                    rotateLeftRBT(grandparent);
                } else { // if node - left child
                    rotateRightRBT(parent);
                    node->color = BLACK;
                    grandparent->color = RED;
                    rotateLeftRBT(grandparent);
                }
            }
        }
    }

    V* findValue(K key) {
        RBNode<K,V>* currNode = root_;
//        if (currNode->key == key || currNode == nullptr)
//            return currNode;
        while (currNode != nullptr) {
            if (key == currNode->key)
                return &(currNode->value);
            else if (key > currNode->key)
                currNode = currNode->rightChild;
            else
                currNode = currNode->leftChild;
        }
        return nullptr;
    }

    void insert(K key, V value) {
//        K key = node.key;
//        V value = node.value;
        RBNode<K, V>* newNode = new RBNode<K, V>(key, value);
        RBNode<K, V>* current = root_;

        if (current == nullptr) { // insert root
            root_ = newNode;
            size_++;
            insertFixup(newNode);
            return;
        }
        while (current != nullptr) {
            if (key > current->key) {
                if (current->rightChild == nullptr) {
                    current->rightChild = newNode;
                    newNode->parent = current;
                    size_++;
                    insertFixup(newNode);
                    return;
                } else
                    current = current->rightChild;
            } else if (key < current->key) {
                if (current->leftChild == nullptr) {
                    current->leftChild = newNode;
                    newNode->parent = current;
                    size_++;
                    insertFixup(newNode);
                    return;
                } else
                    current = current->leftChild;
            } else { // key == current->key
                current->value = value;
                return;
            }
        }
    }

    // Check code below

    RBNode<K, V>* subTreeMin(RBNode<K, V>* node) {
        RBNode<K, V>* currNode = node;
        while (currNode->leftChild != nullptr) {
            currNode = currNode->leftChild;
        }
        return currNode;
//        if (node->leftChild == nullptr)
//            return node;
//        else
//            return subTreeMin(node->leftChild);
    }

    void transplant(RBNode<K, V>* prevNode, RBNode<K, V>* newNode) {
        ///
        if (prevNode->parent == nullptr) {
            root_ = newNode;
        } else {
            RBNode<K, V>* parent = prevNode->parent;
            if (parent->leftChild == prevNode) {
                parent->leftChild = newNode;
            } else {
                parent->rightChild = newNode;
            }
        }
        if (newNode != nullptr) {
            newNode->parent = prevNode->parent;
        }


        ///
//        if (prevNode == root_) {
//            root_ = newNode;
//        }
//        else {
//            RBNode<K, V>* parent = prevNode->parent;
//            if (prevNode == parent->leftChild)
//                parent->leftChild = newNode;
//            else
//                parent->rightChild = newNode;
//
//        }
//
//        ///
//        if (newNode != nullptr) {
//            newNode->parent = prevNode->parent;
//            RBNode<K, V>* leftChild = prevNode->leftChild;
//            RBNode<K, V>* rightChild = prevNode->rightChild;
//            if (leftChild != nullptr) {
//                leftChild->parent = newNode;
//                newNode->leftChild = leftChild;
//            }
//            if (rightChild != nullptr) {
//                rightChild->parent = newNode;
//                newNode->rightChild = rightChild;
//            }
//        }
    }

    void deleteFixup(RBNode<K, V>* node) {
        RBNode<K, V>* currNode = node;
//        while (currNode->color == BLACK) {
        while (currNode != root_ && currNode->color == BLACK) {
//            RBNode<K, V>* currParent = currNode->parent;
            if (currNode->parent == nullptr)
                break;

            if (currNode->parent->leftChild == currNode) { // if the node is or was left child
//            if (currNode->parent->leftChild == currNode) { // won't work after the transplant
//            if (currParent->leftChild == currNode || currParent->leftChild == nullptr) {
                RBNode<K, V>* sibling = currNode->parent->rightChild;
                if (sibling != nullptr) {
                    if (sibling->color == RED) {
                        sibling->color = BLACK;
                        currNode->parent->color = RED;
                        rotateLeftRBT(currNode->parent);
                        RBNode<K, V>* newParent = currNode->parent;
                        sibling = newParent->rightChild;
                    }
                }

//                RBNode<K, V>* siblingLeftChild = sibling->leftChild;
//                RBNode<K, V>* siblingRightChild = sibling->rightChild;
                if ((sibling->leftChild == nullptr || sibling->leftChild->color == BLACK)
                && (sibling->rightChild == nullptr || sibling->rightChild->color == BLACK)) {
//                if ((siblingLeftChild->color == BLACK || siblingLeftChild == nullptr)
//                && (siblingRightChild->color == BLACK || siblingRightChild == nullptr)) {
                    sibling->color = RED;
                    currNode = currNode->parent;
                } else {
                    if ( sibling->rightChild->color == BLACK) {
//                    if ( siblingRightChild->color == BLACK || siblingRightChild == nullptr) {
                        sibling->leftChild->color = BLACK;
                        sibling->color = RED;
                        rotateRightRBT(sibling);
                        sibling = currNode->parent->rightChild;
//                        siblingLeftChild = sibling->leftChild;
//                        siblingRightChild = sibling->rightChild;
                    }
                    sibling->color = currNode->parent->color;
                    currNode->parent->color = BLACK;
                    sibling->rightChild->color = BLACK;
                    rotateLeftRBT(currNode->parent);
                    currNode = root_;
                }
            } else {
                RBNode<K, V>* sibling = currNode->parent->leftChild;
                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    currNode->parent->color = RED;
                    rotateRightRBT(currNode->parent);
                    sibling = currNode->parent->leftChild;
                }
//                RBNode<K, V>* siblingLeftChild = sibling->leftChild;
//                RBNode<K, V>* siblingRightChild = sibling->rightChild;
                if ((sibling->leftChild == nullptr || sibling->leftChild->color == BLACK)
                && (sibling->rightChild == nullptr || sibling->rightChild->color == BLACK)) { // what if sibling's children are nullptr?
//                if ((siblingLeftChild->color == BLACK || siblingLeftChild == nullptr)
//                && (siblingRightChild->color == BLACK || siblingRightChild == nullptr)) {
                    sibling->color = RED;
                    currNode = currNode->parent;
                } else {
                    if (sibling->leftChild->color == BLACK) {
//                    if (sibling->leftChild->color == BLACK || sibling->leftChild == nullptr) {
                        sibling->rightChild->color = BLACK;
                        sibling->color = RED;
                        rotateLeftRBT(sibling);
                        sibling = currNode->parent->leftChild;
//                        RBNode<K, V>* newParent = currNode->parent;
//                        sibling = newParent->leftChild;
//                        sibling->leftChild = sibling->leftChild;
//                        sibling->rightChild = sibling->rightChild;
                    }
                    sibling->color = currNode->parent->color;
                    currNode->parent->color = BLACK;
                    sibling->leftChild->color = BLACK;
                    rotateRightRBT(currNode->parent);
                    currNode = root_;
                }
            }
        }
        currNode->color = BLACK;
    }

    // Check code above

    int getSubtreeHeight(RBNode<K, V>* node) {
        if (node == nullptr)
            return 0;
        else {
            return std::max(getSubtreeHeight(node->leftChild), getSubtreeHeight(node->rightChild)) + 1;
        }
    }

    void printTreeLevel(RBNode<K, V>* subRoot, int level) {
        if (subRoot == nullptr) {
            if (level == 1)
                std::cout << "null ";
            else
                std::cout << "null null ";
        } else if (level == 1) {
            if (subRoot->color == BLACK) {
                std::cout << subRoot->value << " ";
            } else {
                std::cout << "(" << subRoot->value << ") ";
            }
        } else {
            printTreeLevel(subRoot->leftChild, level - 1);
            printTreeLevel(subRoot->rightChild, level - 1);
        }
    }

    std::string treeLevelToString(RBNode<K, V>* subRoot, int level) {
        std::string output = "";
        if (subRoot == nullptr) {
            if (level == 1)
                output += "null ";
            else
                output += "null null ";
        } else if (level == 1) {
            if (subRoot->color == BLACK) {
                output += std::to_string(subRoot->value);
                output += " ";
            } else {
                output += "(";
                output += std::to_string(subRoot->value);
                output += ") ";
            }
        } else {
            output += treeLevelToString(subRoot->leftChild, level - 1);
            output += treeLevelToString(subRoot->rightChild, level - 1);
        }
        return output;
    }

public:

    std::string treeToString() {
        std::string output = "";
        int treeHeight = getSubtreeHeight(root_);
        for (int i = 1; i <= treeHeight; i++) {
            output += treeLevelToString(root_, i);
            output += "; ";
        }

        return output;
    }

    RBNode<K,V>* find(K key) {
        RBNode<K,V>* currNode = root_;
//        if (currNode->key == key || currNode == nullptr)
//            return currNode;
        while (currNode != nullptr) {
            if (key == currNode->key)
                return currNode;
            else if (key > currNode->key)
                currNode = currNode->rightChild;
            else
                currNode = currNode->leftChild;
        }
        return nullptr;
    }

    RBNode<K, V>* root() {
        return root_;
    }

    void printTree() {
        int treeHeight = getSubtreeHeight(root_);
        for (int i = 1; i <= treeHeight; i++) {
            printTreeLevel(root_, i);
            std::cout << "\n";
        }
    }

    class Iterator {
        // Получает ключ в текущей позиции итератора
        const K& key() const;

        const V& get() const;
        // Получает значение в текущей позиции итератора

        void set(const V& value);
//        Устанавливает значение в текущей позиции итератора, сохраняя значение
//                ключа. Ключ отдельно изменить нельзя.

        void next();
//        Перемещает текущую позицию итератора на следующий элемент
//                ассоциативного массива. Порядок обхода неважен, но итератор должен
//                гарантировать, что будут просмотрены все элементы массива, и каждый
//        элемент будет встречен только один раз.

        void prev();
//        Перемещает текущую позицию итератора на предыдущий элемент.

        bool hasNext() const;
//        Возвращает true, если итератор может перейти к следующему элементу,
//        или false, если итератор позиционирован на последний элемент.

        bool hasPrev() const;
//        Возвращает true, если итератор может перейти к предыдущему элементу,
//        или false, если итератор позиционирован на первый элемент.


    };

    Dictionary() {

    } // Создает пустой ассоциативный массив.

    // Деструктор освобождает память, выделенную под хранение элементов. При
    // необходимости, при освобождении памяти вызываются деструкторы
    // хранимых элементов.
    ~Dictionary() {

    }

//    Добавляет переданную пару ключ-значение в ассоциативный массив. Если
//    такой ключ уже существует, связанное с ним значение должно быть
//    заменено на переданное
    void put(const K& key, const V& value) {
        insert(key, value);
    }

    // Удаляет элемент с указанным ключом из ассоциативного массива
    void remove(const K& key) { // !!! CHECK
        RBNode<K, V>* delNode = find(key); // z in CLRS
        if (delNode == nullptr)
            return;
//        if (delNode == root_) { // WRONG!
//            root_ = nullptr;
//            size_--;
//            return;
//        }

        RBNode<K, V>* successorNode = delNode; // y in CLRS
        RBNode<K, V>* x = nullptr; // x in CLRS
        bool originalColor = delNode->color; // y-original-color in CLRS

        bool wasCreatedNil = false;

        ///
        if (delNode->leftChild == nullptr && delNode->rightChild == nullptr) {
            if (delNode == root_) {
                root_ = nullptr;
                size_--;
                return;
            }
        }
        ///

        if (delNode->leftChild == nullptr) {
            x = delNode->rightChild; // may be null
            if (x == nullptr) {
                x = initializeTreeNullForRemove(delNode);
                wasCreatedNil = true;
            }
            transplant(delNode, x);
        } else if (delNode->rightChild == nullptr) {
            x = delNode->leftChild; // is not null!
            transplant(delNode, x);
        } else {
            successorNode = subTreeMin(delNode->rightChild); // can it be null?? no, at least right child exists
            originalColor = successorNode->color;
            x = successorNode->rightChild; // what if it is null???
            if (x == nullptr) { //  && delNode == root_
                // надо сделать искусственный узел в x, иначе fixup вызовется от корня и ничего не сбалансируется
                x = initializeTreeNullForRemove(successorNode);
                wasCreatedNil = true;
            }

            if (successorNode->parent != delNode) {
                transplant(successorNode, successorNode->rightChild);
                successorNode->rightChild = delNode->rightChild; // what if it is null??
                successorNode->rightChild->parent = successorNode; // what if it is null??
            }
            ///
//            if (successorNode->parent == delNode) {
//                if (x != nullptr) { // what if it is null???
//                    x->parent = successorNode;
//                }
//            } else {
//                transplant(successorNode, successorNode->rightChild);
//                successorNode->rightChild = delNode->rightChild; // what if it is null??
//                successorNode->rightChild->parent = successorNode; // what if it is null??
////                RBNode<K, V>* succRightChild = successorNode->rightChild;
////                succRightChild = delNode->rightChild;
////                succRightChild->parent = successorNode;
//            }
            ///
            transplant(delNode, successorNode);
            successorNode->leftChild = delNode->leftChild;
            successorNode->leftChild->parent = successorNode;
            successorNode->color = delNode->color;
//            RBNode<K, V>* succLeftChild = successorNode->leftChild;
//            succLeftChild = delNode->leftChild;
//            succLeftChild->parent = successorNode;
//            successorNode->color = delNode->color;
        }

//        delete delNode; // ???

        if (originalColor == BLACK) {
            if (x != nullptr) {
                deleteFixup(x);
                if (wasCreatedNil) {
                    // нужно удалить искусственно созданный лист
                    if (x->parent->leftChild == x)
                        x->parent->leftChild = nullptr;
                    else
                        x->parent->rightChild = nullptr;
                    delete x;
                }
            } else
                deleteFixup(successorNode);
        }

        size_--;
    }

    // Возвращает true, если в ассоциативном массиве существует элемент с
    //указанным ключом.
    bool contains(const K& key) {
        return (find(key) != nullptr);
    }

    // Оператор индексирования позволяет обратиться к элементу
    //ассоциативного массива по ключу для чтения и для записи. Если элемента
    //с таким ключом нет, то неконстантный оператор должен его создать и
    //добавить в ассоциативный массив со значением по умолчанию.
    //Константная версия оператора должна просто вернуть значение по
    //умолчанию.
    const V& operator[](const K& key) const {
        V* searchResult = findValue(key);
        if (searchResult != nullptr)
            return *searchResult;
        else
            return getDefaultValue();
    }

    V& operator[](const K& key) {
        V* searchResult = findValue(key);
        if (searchResult != nullptr)
            return *searchResult;
        else {
            insert(key, getDefaultValue());
            return getDefaultValue();
        }
    }

    V& getDefaultValue() {
        return *new V();
    }

    int size() const {
        return size_;
    }

    // Возвращает итератор, указывающий на первый элемент массива.
    Iterator iterator();
    const Iterator iterator() const;

    // Необходимо либо предоставить
    // правильный механизм копирования и присваивания, либо запретить его.
    // copy
    Dictionary(const Dictionary &a) = delete;
    //assignment
    Dictionary operator=(const Dictionary &a) = delete;
};

#endif //P3_SEARCH_DICTIONARY_H
