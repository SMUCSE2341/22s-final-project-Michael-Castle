
#include "parsingData.h"


int main(int argc, char* const args[]) {
    string searchWord = args[2];
    string DataSet = args[1];
    Directory newDirec;
    searchWord = newDirec.stemWord(searchWord);

    word myWord;
    myWord.id = searchWord;

    newDirec.createStopMap();
    newDirec.open_dir_using_filesystem(DataSet);

    newDirec.SearchWord(myWord);

    cout << "hello";
    // Create a hash table with 3 indices:
//    HashTable ht;
//
//    string first = "Michael";
//    string second = "William";
//    string third = "Kevin";
//    vector<string> testVector;
//    testVector.push_back("1");
//    testVector.push_back("2");
//    testVector.push_back("3");
//    testVector.push_back("4");
//
//    ht.insertElement(first, testVector);
//    ht.insertElement(second, testVector);
//    ht.insertElement(second, testVector);
//    ht.insertElement(third, testVector);
//    vector<string> outVector = ht.find(first) ;
//    cout << outVector.at(1) << endl;



    return 0;

}