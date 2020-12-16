#include "gtest/gtest.h"
#include "../Dictionary.h"

TEST(dictionaryTest, size) {
    Dictionary<int, int> myDictionary;
    ASSERT_EQ(myDictionary.size(), 0);
    for (int i = 1; i <= 20; i++) {
        myDictionary.put(i, i);
        ASSERT_EQ(myDictionary.size(), i);
    }
}

TEST(dictionaryTest, putRoot) {
    Dictionary<int, int> myDictionary;
    myDictionary.put(13, 13);
    ASSERT_EQ(myDictionary.size(), 1);
    ASSERT_EQ(myDictionary.root()->key, 13);
    ASSERT_EQ(myDictionary.root()->value, 13);
    ASSERT_EQ(myDictionary.root()->color, BLACK);
}

TEST(dictionaryTest, putChildOfBlackNode) {
    Dictionary<int, int> myDictionary;
    myDictionary.put(13, 13);
    myDictionary.put(5, 5);
    ASSERT_EQ(myDictionary.size(), 2);
    ASSERT_EQ(myDictionary.find(5)->value, 5);
    ASSERT_EQ(myDictionary.find(5)->color, RED);
    ASSERT_EQ(myDictionary.find(5)->parent, myDictionary.root());

    myDictionary.put(25, 25);
    ASSERT_EQ(myDictionary.size(), 3);
    ASSERT_EQ(myDictionary.find(25)->value, 25);
    ASSERT_EQ(myDictionary.find(25)->color, RED);
    ASSERT_EQ(myDictionary.find(25)->parent, myDictionary.root());

//    myDictionary.printTree();
}

TEST(dictionaryTest, putRedParentAndUncle1) {
    Dictionary<int, int> myDictionary;
    myDictionary.put(13, 13);
    myDictionary.put(5, 5);
    myDictionary.put(25, 25);

    myDictionary.put(1, 1);
    ASSERT_EQ(myDictionary.size(), 4);
    ASSERT_EQ(myDictionary.find(1)->value, 1);
    ASSERT_EQ(myDictionary.find(1)->color, RED);
    ASSERT_EQ(myDictionary.find(1)->parent, myDictionary.find(5));
    ASSERT_EQ(myDictionary.find(5)->color, BLACK);
    ASSERT_EQ(myDictionary.find(25)->color, BLACK);

//    myDictionary.printTree();
}

TEST(dictionaryTest, putRedParentAndUncle2) {
    Dictionary<int, int> myDictionary;
    myDictionary.put(13, 13);
    myDictionary.put(5, 5);
    myDictionary.put(25, 25);

    myDictionary.put(7, 7);
    ASSERT_EQ(myDictionary.size(), 4);
    ASSERT_EQ(myDictionary.find(7)->value, 7);
    ASSERT_EQ(myDictionary.find(7)->color, RED);
    ASSERT_EQ(myDictionary.find(7)->parent, myDictionary.find(5));
    ASSERT_EQ(myDictionary.find(5)->color, BLACK);
    ASSERT_EQ(myDictionary.find(25)->color, BLACK);

//    myDictionary.printTree();
}

TEST(dictionaryTest, putRedParentAndUncle3) {
    Dictionary<int, int> myDictionary;
    myDictionary.put(13, 13);
    myDictionary.put(5, 5);
    myDictionary.put(25, 25);

    myDictionary.put(15, 15);
    ASSERT_EQ(myDictionary.size(), 4);
    ASSERT_EQ(myDictionary.find(15)->value, 15);
    ASSERT_EQ(myDictionary.find(15)->color, RED);
    ASSERT_EQ(myDictionary.find(15)->parent, myDictionary.find(25));
    ASSERT_EQ(myDictionary.find(5)->color, BLACK);
    ASSERT_EQ(myDictionary.find(25)->color, BLACK);

//    myDictionary.printTree();
}

TEST(dictionaryTest, putRedParentAndUncle4) {
    Dictionary<int, int> myDictionary;
    myDictionary.put(13, 13);
    myDictionary.put(5, 5);
    myDictionary.put(25, 25);

    myDictionary.put(27, 27);
    ASSERT_EQ(myDictionary.size(), 4);
    ASSERT_EQ(myDictionary.find(27)->value, 27);
    ASSERT_EQ(myDictionary.find(27)->color, RED);
    ASSERT_EQ(myDictionary.find(27)->parent, myDictionary.find(25));
    ASSERT_EQ(myDictionary.find(5)->color, BLACK);
    ASSERT_EQ(myDictionary.find(25)->color, BLACK);

//    myDictionary.printTree();
}

TEST(dictionaryTest, putRedParent1) {
    Dictionary<int, int> myDictionary;
    myDictionary.put(13, 13);
    myDictionary.put(5, 5);
    // parent is left child
    // new node is left child

    myDictionary.put(2, 2);
    ASSERT_EQ(myDictionary.size(), 3);
    // parent is now black
    ASSERT_EQ(myDictionary.find(5)->color, BLACK);
    // grandparent is now red
    ASSERT_EQ(myDictionary.find(13)->color, RED);
    // after right rotation
    ASSERT_EQ(myDictionary.root()->value, 5);
    ASSERT_EQ(myDictionary.root()->rightChild, myDictionary.find(13));

//    myDictionary.printTree();
}

TEST(dictionaryTest, putRedParent2) {
    Dictionary<int, int> myDictionary;
    myDictionary.put(13, 13);
    myDictionary.put(5, 5);
    // parent is left child
    // new node is right child

    myDictionary.put(7, 7);
    ASSERT_EQ(myDictionary.size(), 3);
    // node is now black
    ASSERT_EQ(myDictionary.find(7)->color, BLACK);
    // grandparent is now red
    ASSERT_EQ(myDictionary.find(13)->color, RED);
    // after rotation
    ASSERT_EQ(myDictionary.root()->value, 7);
    ASSERT_EQ(myDictionary.find(7)->leftChild, myDictionary.find(5));
    ASSERT_EQ(myDictionary.find(7)->rightChild, myDictionary.find(13));

//    myDictionary.printTree();
}

TEST(dictionaryTest, putRedParent3) {
    Dictionary<int, int> myDictionary;
    myDictionary.put(13, 13);
    myDictionary.put(25, 25);
    // parent is right child
    // new node is right child

    myDictionary.put(27, 27);

    ASSERT_EQ(myDictionary.size(), 3);
    // parent is now black
    ASSERT_EQ(myDictionary.find(25)->color, BLACK);
    // grandparent is now red
    ASSERT_EQ(myDictionary.find(13)->color, RED);
    // after left rotation
    ASSERT_EQ(myDictionary.root()->value, 25);
    ASSERT_EQ(myDictionary.find(25)->leftChild, myDictionary.find(13));

//    myDictionary.printTree();
}

TEST(dictionaryTest, putRedParent4) {
    Dictionary<int, int> myDictionary;
    myDictionary.put(13, 13);
    myDictionary.put(25, 25);
    // parent is right child
    // new node is left child

    myDictionary.put(18, 18);
    // rotateRightRBT(parent);
    //                    node->color = BLACK;
    //                    grandparent->color = RED;
    //                    rotateLeftRBT(grandparent);
    ASSERT_EQ(myDictionary.size(), 3);
    // node is now black
    ASSERT_EQ(myDictionary.find(18)->color, BLACK);
    // grandparent is now red
    ASSERT_EQ(myDictionary.find(13)->color, RED);
    // after right rotation
    ASSERT_EQ(myDictionary.find(18)->rightChild, myDictionary.find(25));
    // after left rotation
    ASSERT_EQ(myDictionary.root()->value, 18);
    ASSERT_EQ(myDictionary.root()->leftChild, myDictionary.find(13));

//    myDictionary.printTree();
}

TEST(dictionaryTest, contains) {
    Dictionary<int, int> myDictionary;
    ASSERT_FALSE(myDictionary.contains(25));
    myDictionary.put(25, 25);
    ASSERT_TRUE(myDictionary.contains(25));
}

TEST(dictionaryTest, removeTheOnlyElement) {
    Dictionary<int, int> myDictionary;
    myDictionary.put(13, 13);
    ASSERT_EQ(myDictionary.size(), 1);
    myDictionary.remove(13);
    ASSERT_EQ(myDictionary.size(), 0);
    ASSERT_EQ(myDictionary.root(), nullptr);
}

TEST(dictionaryTest, removeNonExisting) {
    Dictionary<int, int> myDictionary;
    myDictionary.put(13, 13);
    ASSERT_EQ(myDictionary.size(), 1);
    myDictionary.remove(3);
    ASSERT_EQ(myDictionary.size(), 1);
}

TEST(dictionaryTest, removeRedLeaf) {
    Dictionary<int, int> myDictionary;
    myDictionary.put(13, 13);
    myDictionary.put(4, 4);
    ASSERT_EQ(myDictionary.size(), 2);
    // 13
    // (4) null

    myDictionary.remove(4);
    ASSERT_EQ(myDictionary.size(), 1);
    ASSERT_EQ(myDictionary.find(4), nullptr);
}

TEST(dictionaryTest, removeBlackLeaf1) {
    Dictionary<int, int> myDictionary;
    myDictionary.put(13, 13);
    myDictionary.put(7, 7);
    myDictionary.put(20, 20);
    myDictionary.put(3, 3);
    myDictionary.remove(3);
    ASSERT_EQ(myDictionary.size(), 3);
    // 13
    // 7 20

    myDictionary.remove(7);
    // 13
    // null (20)

    ASSERT_EQ(myDictionary.size(), 2);
    ASSERT_EQ(myDictionary.find(7), nullptr);
    ASSERT_EQ(myDictionary.find(20)->color, RED);
    ASSERT_EQ(myDictionary.find(13)->leftChild, nullptr);
}

TEST(dictionaryTest, removeBlackLeaf2) {
    Dictionary<int, int> myDictionary;
    myDictionary.put(13, 13);
    myDictionary.put(7, 7);
    myDictionary.put(20, 20);
    myDictionary.put(3, 3);
    myDictionary.remove(3);
    ASSERT_EQ(myDictionary.size(), 3);
    // 13
    // 7 20

    myDictionary.remove(20);
    // 13
    // (7) null

    ASSERT_EQ(myDictionary.size(), 2);
    ASSERT_EQ(myDictionary.find(20), nullptr);
    ASSERT_EQ(myDictionary.find(7)->color, RED);
    ASSERT_EQ(myDictionary.find(13)->rightChild, nullptr);
}

TEST(dictionaryTest, removeBigTree) {
    Dictionary<int, int> myDictionary;
    myDictionary.put(4, 4);
    myDictionary.put(2, 2);
    myDictionary.put(1, 1);
    myDictionary.put(3, 3);
    myDictionary.put(6, 6);
    myDictionary.put(5, 5);
    myDictionary.put(9, 9);
    myDictionary.put(7, 7);
    myDictionary.put(8, 8);
    myDictionary.put(10, 10);
    //4
    //2 6
    //1 3 5 (8)
    //null null null null null null 7 9
    //null null null null null null null null null null null null null null null (10)

    myDictionary.printTree();

    ASSERT_EQ(myDictionary.size(), 10);
    ASSERT_EQ(myDictionary.treeToString(), "4 ; "
                                                     "2 6 ; "
                                                     "1 3 5 (8) ; "
                                                     "null null null null null null 7 9 ; "
                                                     "null null null null null null null null null null null null null null null (10) ; ");

    myDictionary.remove(1); // remove leaf
    ASSERT_EQ(myDictionary.size(), 9);
    ASSERT_EQ(myDictionary.treeToString(), "6 ; "
                                                     "4 8 ; "
                                                     "2 5 7 9 ; "
                                                     "null (3) null null null null null (10) ; ");

    myDictionary.remove(2); // remove element with one child
    ASSERT_EQ(myDictionary.size(), 8);
    ASSERT_EQ(myDictionary.treeToString(), "6 ; "
                                                     "4 8 ; "
                                                     "3 5 7 9 ; "
                                                     "null null null null null null null (10) ; ");

//    myDictionary.printTree();
    myDictionary.remove(6); // remove element with two children
//    ASSERT_EQ(myDictionary.size(), 7);

//    myDictionary.remove(4); // remove root

//    std::cout << myDictionary.root()->value << "\n";
//    std::cout << myDictionary.root()->leftChild->value << " " <<  myDictionary.root()->rightChild->value << "\n";
//    std::cout << myDictionary.find(8)->parent->value << "\n";
//    std::cout << myDictionary.find(5)->parent->value;

    myDictionary.printTree();
//    std::cout << myDictionary.find(8)->parent->value;
//    std::cout << "\n";
//    std::cout << myDictionary.treeToString();
}