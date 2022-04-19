
#include "parsingData.h"


int main(int argc, char* const args[]) {
    string DataSet = args[1];
    string searchWord = args[2];
    Directory newDirec;
    searchWord = newDirec.stemWord(searchWord);

    word myWord;
    myWord.id = searchWord;

    newDirec.createStopMap();
    newDirec.open_dir_using_filesystem(DataSet);

    newDirec.SearchWord(myWord);
    //newDirec.ParseData("/Users/michael_castle/Desktop/data structures/22s-final-project-william-kornreich/TestingDataSet/FirstGroup/blogs_0000001.json");
    // 1. Parse a JSON string into DOM.



    return 0;

}