
#include <sstream>
#include "parsingData.h"


int main(int argc, char* const args[]) {
    string searchWord = args[1];
    string DataSet = args[2];
    Directory newDirec;
    searchWord = newDirec.stemWord(searchWord);

    word myWord;
    myWord.id = searchWord;

    newDirec.createStopMap();
    newDirec.open_dir_using_filesystem(DataSet);

    string usrInput;
    cout << "please enter search query, or 'q' to quit." << endl;
    getline(cin, usrInput);
    bool andQuery = true;
    bool orQuery = false;
    bool notQuery = false;

    bool word = true;
    bool person = false;
    bool org = false;
    std::string stringvalues = "125 320 512 750 333";
    std::istringstream iss (usrInput);
    vector<string> inputVector;
    string tmp;

    vector<string> wordVector;
    vector<string> personVector;
    vector<string> orgVector;
    vector<string> notWordVector;
    vector<string> notPersonVector;
    vector<string> notOrgVector;


    //TODO at the end just use the function you made in parsingData with all 6 vectors pretty close to done. then loop
    // around until first input is q. remember to add some extra check so that it doesnt auto exit if the first letter is
    // q for a longer query.


    while(!iss.eof()) {
        iss >> tmp;
        inputVector.push_back(tmp);
    }
    for(int i = 0; i < inputVector.size(); i++) {
        cout << inputVector.at(i) << endl;
    }

    for(int i = 0; i < inputVector.size(); i++) {
        if(inputVector.at(i) == "AND") {

        }
        else if(inputVector.at(i) == "OR") {
            andQuery = false;
            orQuery = true;
        }
        else if(inputVector.at(i) == "PERSON") {
            word = false;
            person = true;
            org = false;
        }
        else if(inputVector.at(i) == "ORG") {
            word = false;
            person = false;
            org = true;
        }
        else if(inputVector.at(i) == "NOT") {
            notQuery = true;
            word = true;
            person = false;
            org = false;
        }
        else {//push to respective lists here. not that much work maybe 15 minutes
            if(!notQuery) {
               if(word) {
                   wordVector.push_back(inputVector.at(i));
               }
               else if (person) {
                   personVector.push_back(inputVector.at(i));
               }
               else if(org ) {
                   personVector.push_back(inputVector.at(i));
               }

            }
            else {
                if(word) {
                    notWordVector.push_back(inputVector.at(i));
                }
                else if (person) {
                    personVector.push_back(inputVector.at(i));
                }
                else if(org ) {
                    personVector.push_back(inputVector.at(i));
                }
            }
        }
    }








    //cout << "hello";
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