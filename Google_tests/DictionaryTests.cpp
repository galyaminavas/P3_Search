#include <utility>

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

TEST(dictionaryTest, putUpdateValue) {
    Dictionary<int, int> myDictionary;
    myDictionary.put(13, 13);
    ASSERT_EQ(myDictionary.size(), 1);
    ASSERT_EQ(myDictionary.find(13)->value, 13);
    myDictionary.put(13, 100);
    ASSERT_EQ(myDictionary.size(), 1);
    ASSERT_EQ(myDictionary.find(13)->value, 100);
}

TEST(dictionaryTest, contains) {
    Dictionary<int, int> myDictionary;
    ASSERT_FALSE(myDictionary.contains(25));
    myDictionary.put(25, 25);
    ASSERT_TRUE(myDictionary.contains(25));
    myDictionary.put(100, 100);
    ASSERT_TRUE(myDictionary.contains(100));
    myDictionary.remove(100);
    ASSERT_FALSE(myDictionary.contains(100));
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


    myDictionary.remove(6); // remove root element with two children
    ASSERT_EQ(myDictionary.size(), 7);
    ASSERT_EQ(myDictionary.treeToString(), "7 ; "
                                                     "4 9 ; "
                                                     "3 5 8 10 ; ");

    myDictionary.remove(4); // remove element with two children
    ASSERT_EQ(myDictionary.size(), 6);
    ASSERT_EQ(myDictionary.treeToString(), "7 ; "
                                                     "5 (9) ; "
                                                     "(3) null 8 10 ; ");

    ASSERT_EQ(myDictionary.root(), myDictionary.find(7));
    ASSERT_EQ(myDictionary.find(7)->color, BLACK);
    ASSERT_EQ(myDictionary.find(7)->parent, nullptr);
    ASSERT_EQ(myDictionary.find(7)->leftChild, myDictionary.find(5));
    ASSERT_EQ(myDictionary.find(7)->rightChild, myDictionary.find(9));

    ASSERT_EQ(myDictionary.find(5)->color, BLACK);
    ASSERT_EQ(myDictionary.find(5)->parent, myDictionary.find(7));
    ASSERT_EQ(myDictionary.find(5)->leftChild, myDictionary.find(3));
    ASSERT_EQ(myDictionary.find(5)->rightChild, nullptr);

    ASSERT_EQ(myDictionary.find(9)->color, RED);
    ASSERT_EQ(myDictionary.find(9)->parent, myDictionary.find(7));
    ASSERT_EQ(myDictionary.find(9)->leftChild, myDictionary.find(8));
    ASSERT_EQ(myDictionary.find(9)->rightChild, myDictionary.find(10));

    ASSERT_EQ(myDictionary.find(3)->color, RED);
    ASSERT_EQ(myDictionary.find(3)->parent, myDictionary.find(5));
    ASSERT_EQ(myDictionary.find(3)->leftChild, nullptr);
    ASSERT_EQ(myDictionary.find(3)->rightChild, nullptr);

    ASSERT_EQ(myDictionary.find(8)->color, BLACK);
    ASSERT_EQ(myDictionary.find(8)->parent, myDictionary.find(9));
    ASSERT_EQ(myDictionary.find(8)->leftChild, nullptr);
    ASSERT_EQ(myDictionary.find(8)->rightChild, nullptr);

    ASSERT_EQ(myDictionary.find(10)->color, BLACK);
    ASSERT_EQ(myDictionary.find(10)->parent, myDictionary.find(9));
    ASSERT_EQ(myDictionary.find(10)->leftChild, nullptr);
    ASSERT_EQ(myDictionary.find(10)->rightChild, nullptr);
}

TEST(dictionaryTest, index) {
    const Dictionary<int, int> myDictionaryConst;
    ASSERT_EQ(myDictionaryConst.size(), 0);
    int value = myDictionaryConst[128];
    ASSERT_EQ(myDictionaryConst.size(), 0);

    Dictionary<int, int> myDictionary;
    ASSERT_EQ(myDictionary.size(), 0);
    myDictionary.put(10, 10);
    ASSERT_EQ(myDictionary.size(), 1);
    int value1 = myDictionary[10];
    ASSERT_EQ(value1, 10);
    ASSERT_EQ(myDictionary.size(), 1);
    myDictionary[10] = 100;
    ASSERT_EQ(myDictionary.find(10)->value, 100);
    ASSERT_EQ(myDictionary.size(), 1);

    int value2 = myDictionary[50];
    ASSERT_EQ(myDictionary.size(), 2);
    ASSERT_EQ(myDictionary.find(50)->value, 0);

}

TEST(dictionaryTest, iterator) {
    int numbers[10];
    numbers[0] = 1;
    numbers[1] = 2;
    numbers[2] = 3;
    numbers[3] = 4;
    numbers[4] = 5;
    numbers[5] = 6;
    numbers[6] = 7;
    numbers[7] = 8;
    numbers[8] = 9;
    numbers[9] = 10;

    Dictionary<int, int> myDictionary;
    myDictionary.put(numbers[9], numbers[9]);
    myDictionary.put(numbers[8], numbers[8]);
    myDictionary.put(numbers[7], numbers[7]);
    myDictionary.put(numbers[6], numbers[6]);
    myDictionary.put(numbers[5], numbers[5]);
    myDictionary.put(numbers[4], numbers[4]);
    myDictionary.put(numbers[3], numbers[3]);
    myDictionary.put(numbers[2], numbers[2]);
    myDictionary.put(numbers[1], numbers[1]);
    myDictionary.put(numbers[0], numbers[0]);

    int numbersIndex = 0;
    auto it = myDictionary.iterator();
    while (it.hasNext()) {
        ASSERT_EQ(it.key(), numbersIndex + 1);
        ASSERT_EQ(it.get(), numbers[numbersIndex]);
        numbersIndex++;
        it.next();
    }
    ASSERT_EQ(it.key(), 10);
    ASSERT_EQ(it.get(), numbers[9]);

    while (it.hasPrev()) {
        ASSERT_EQ(it.key(), numbersIndex + 1);
        ASSERT_EQ(it.get(), numbers[numbersIndex]);
        numbersIndex--;
        it.prev();
    }
    ASSERT_EQ(it.key(), 1);
    ASSERT_EQ(it.get(), numbers[0]);

    it.set(100);
    ASSERT_EQ(myDictionary.find(1)->value, 100);
}

TEST(dictionaryTest, testString) {
    Dictionary<std::string, int> npc;
    npc.put("health", 10);
    npc.put("armor", 20);
    npc.put("ammo", 5);

    ASSERT_TRUE(npc.contains("health"));
    ASSERT_TRUE(npc.contains("armor"));
    ASSERT_TRUE(npc.contains("ammo"));
    ASSERT_FALSE(npc.contains("mana"));

    ASSERT_EQ(npc.size(), 3);
    ASSERT_EQ(npc["health"], 10);
    ASSERT_EQ(npc["armor"], 20);
    ASSERT_EQ(npc["ammo"], 5);
}

TEST(dicionaryTest, testClass) {
    class Character {
    public:
        std::string name;
        int hp;
        std::size_t hash;

        Character() {
//            std::cout << "Character()\n";
        }

        Character(std::string name_, int hp_) {
//            std::cout << "Character(name, hp)\n";
            name = std::move(name_);
            hp = hp_;
            std::size_t hash1 = std::hash<std::string>{}(name);
            std::size_t hash2 = std::hash<int>{}(hp);
            hash = hash1 ^ (hash2 << 1);
//            std::cout << hash << "\n";
        }

        ~Character() {
//            std::cout << "~Character()\n";
        }

        bool operator<(const Character& ch) const {
            return hash < ch.hash;
        }

        bool operator==(const Character& ch) const {
            return hash == ch.hash;
        }

        bool operator>(const Character& ch) const {
            return hash > ch.hash;
        }
    };

    Character ch1 = Character("Leela", 2000);
    std::string role1 = "Pilot";
    Character ch2 = Character("Bender", 1024);
    std::string role2 = "Robot";
    Character ch3 = Character("Farnsworth", 128);
    std::string role3 = "Crazy scientist";

    Dictionary<Character, std::string> myCharacters;
    myCharacters.put(ch1, role1);
    myCharacters.put(ch2, role2);
    myCharacters.put(ch3, role3);

    ASSERT_EQ(myCharacters.size(), 3);
    ASSERT_TRUE(myCharacters.contains(ch1));
    ASSERT_TRUE(myCharacters.contains(ch2));
    ASSERT_TRUE(myCharacters.contains(ch3));
    ASSERT_EQ(myCharacters[ch1], role1);
    ASSERT_EQ(myCharacters[ch2], role2);
    ASSERT_EQ(myCharacters[ch3], role3);

    myCharacters.remove(ch3);
    ASSERT_EQ(myCharacters.size(), 2);
    ASSERT_FALSE(myCharacters.contains(ch3));
}