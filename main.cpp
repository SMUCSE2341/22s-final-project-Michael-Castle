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
    node1.left = &node2;
    node2.left = &node3;
    node3.left = &node4;

    node5 = *myTree.findValue(5, &node1);
    std:: cout << node5.data;
    std::cout << myTree.getBalance(&node1);



    return 0;

}