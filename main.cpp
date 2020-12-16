#include <iostream>
#include "Dictionary.h"

int main() {
    Dictionary<int, int> myDictionary;
    myDictionary.put(10, 10);
//    myDictionary.printTree();
    myDictionary.put(8, 8);
//    myDictionary.printTree();

    myDictionary.put(15, 15);
//    myDictionary.put(20,20);
//    myDictionary.remove(15);
    myDictionary.remove(10);
    myDictionary.printTree();

    return 0;
}
