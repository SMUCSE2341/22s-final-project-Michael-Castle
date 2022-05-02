
#include "parsingData.h"
#include "vectorHelper.h"
using namespace std;
int main(int argc, char* const args[]) {
    string DataSet = args[1];
    string searchWord = args[2];
    Directory newDirec;
    searchWord = newDirec.stemWord(searchWord);

    word myWord;
    word myWord2;
    myWord.id = searchWord;
    myWord2.id = newDirec.stemWord("market");

    newDirec.createStopMap();
    newDirec.open_dir_using_filesystem(DataSet);


    //newDirec.ParseData("/Users/michael_castle/Desktop/data structures/22s-final-project-william-kornreich/TestingDataSet/FirstGroup/blogs_0000001.json");
    // 1. Parse a JSON string into DOM.

    vector<string> empty;
    vector<string> testVector1;
    vector<string> testVector2 = newDirec.SearchWord(myWord2);
    vector<string> testVector3;
    testVector3 = newDirec.SearchWord(myWord);

    for(string tmp : testVector3) {
        cout << tmp << endl;
    }
    cout << endl;
    for(string tmp : testVector2) {
        cout << tmp << endl;
    }
    cout << endl;
    testVector1.push_back("market");
    testVector1.push_back("market");

    vector<string> testVector4 = newDirec.searchAnd(testVector1, empty, empty, empty, empty, empty);

    for(string tmp : testVector4) {
        cout << tmp << endl;
    }







    return 0;

}