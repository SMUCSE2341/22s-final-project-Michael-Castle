// rapidjson/example/simpledom/simpledom.cpp`
#include "DSAvlTree.h"
#include <iostream>
using namespace std;

int main() {
    // 1. Parse a JSON string into DOM.
    DSNode<int> node1(1);
    DSNode<int> node2(5);
    DSNode<int> node3(4);
    DSNode<int> node4(8);
    DSNode<int> node5(3);

    DSTree<int> myTree;
    myTree.head = &node1;
    int x = 3;
    myTree.insert(x);
    myTree.insert(2);
    myTree.insert(4);
    myTree.insert(5);
    myTree.insert(6);
    myTree.insert(7);
    myTree.insert(8);
    myTree.insert(12);
    myTree.insert(62);
    myTree.insert(3);
    myTree.insert(5);
    myTree.insert(9);
    myTree.insert(6);



    //node5 = *myTree.findValue(5, &node1);

    std::cout << myTree.getBalance(&node1);



    return 0;

}