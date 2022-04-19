
#include "parsingData.h"
using namespace std;

int main() {


    Directory newDirec;
    newDirec.open_dir_using_filesystem("TestingDataSet");
    //newDirec.ParseData("/Users/michael_castle/Desktop/data structures/22s-final-project-william-kornreich/TestingDataSet/FirstGroup/blogs_0000001.json");
    // 1. Parse a JSON string into DOM.


    DSNode<int> node1(1);


    DSTree<int> myTree;
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

    word jacobBarcalona("hello");
    word newWord1("aello");
    word newWord2("bello");
    word newWord3("cello");
    word newWord4("dello");
    word newWord5("eello");
    word newWord6("fello");

    DSTree<word> wordTree;

    wordTree.insert(jacobBarcalona);
    wordTree.insert(newWord1);
    wordTree.insert(newWord2);
    wordTree.insert(newWord3);
    wordTree.insert(newWord4);
    wordTree.insert(newWord5);
    wordTree.insert(newWord6);

    DSNode<int>* n = new DSNode<int>(5);
    delete n;
    //node5 = *myTree.findValue(5, &node1);

    std::cout << myTree.getBalance(&node1);



    return 0;

}