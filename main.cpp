
#include <sstream>
#include "parsingData.h"
#include <algorithm>
#include <chrono>


int main(int argc, char* const args[]) {
    string searchWord = args[2];
    string DataSet = args[1];
    Directory newDirec;
    searchWord = newDirec.stemWord(searchWord);

    word myWord;
    myWord.id = searchWord;

    newDirec.createStopMap();
    newDirec.open_dir_using_filesystem(DataSet);

    vector<word> allWords = newDirec.index.toVector();
    vector<pair<int,string>> wordFreq;
    for(int i = 0; i < allWords.size(); i++) {
        wordFreq.push_back(make_pair(allWords.at(i).count,allWords.at(i).id));
    }
    cout << "most common words" << endl;
    sort(wordFreq.begin(), wordFreq.end());
    for(int i = 1; i < 26; i++ ) {
        cout << i << ": " << wordFreq.at(wordFreq.size()-i).second << "count: " << wordFreq.at(wordFreq.size()-i).first << endl;
    }



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

    while(usrInput.size() > 1 && usrInput[0] != 'q') {
        std::istringstream iss (usrInput);
        while (!iss.eof()) {
            iss >> tmp;
            inputVector.push_back(tmp);
        }
        for (int i = 0; i < inputVector.size(); i++) {
            //cout << inputVector.at(i) << endl;
        }

        for (int i = 0; i < inputVector.size(); i++) {
            if (inputVector.at(i) == "AND") {

            } else if (inputVector.at(i) == "OR") {
                andQuery = false;
                orQuery = true;
            } else if (inputVector.at(i) == "PERSON") {
                word = false;
                person = true;
                org = false;
            } else if (inputVector.at(i) == "ORG") {
                word = false;
                person = false;
                org = true;
            } else if (inputVector.at(i) == "NOT") {
                notQuery = true;
                word = true;
                person = false;
                org = false;
            } else {//push to respective lists here. not that much work maybe 15 minutes
                if (!notQuery) {
                    if (word) {
                        wordVector.push_back(inputVector.at(i));
                    } else if (person) {
                        personVector.push_back(inputVector.at(i));
                    } else if (org) {
                        orgVector.push_back(inputVector.at(i));
                    }

                } else {
                    if (word) {
                        notWordVector.push_back(inputVector.at(i));
                    } else if (person) {
                        notPersonVector.push_back(inputVector.at(i));
                    } else if (org) {
                        notOrgVector.push_back(inputVector.at(i));
                    }
                }
            }
        }
        vector<string> searchVector;
        if(orQuery) {
            searchVector = newDirec.searchOr(wordVector, personVector, orgVector, notWordVector,
                                             notPersonVector, notOrgVector);
        }
        else {
            searchVector = newDirec.searchAnd(wordVector, personVector, orgVector, notWordVector,
                                             notPersonVector, notOrgVector);
        }
        vector<string> rankedIDs = newDirec.Ranking(searchVector, wordVector);
        string docText;
        for (int i = 0; i < rankedIDs.size(); i++) {
            docText = newDirec.getText(rankedIDs.at(i));
            cout << i+1 << ": ";
            for(int j = 0; j < 60 & j < docText.size(); j++) {
                cout << docText[j];
            }
            cout << endl;
            for(int j = 61; j < 120 & j < docText.size(); j++) {
                cout << docText[j];
            }
            cout << "..." << endl << endl;

        }
        cout << endl << "please enter the document number which you want to read" << endl;
        int docNum;
        cin >> docNum;
        docNum--;
        if(docNum < rankedIDs.size() && docNum >= 0) {
            cout << newDirec.getText(rankedIDs.at(docNum)) << endl;
        }
        cin.get();

        cout << endl << "please enter search query, or 'q' to quit." << endl;
        getline(cin, usrInput);

        andQuery = true;
        orQuery = false;
        notQuery = false;

        word = true;
        person = false;
        org = false;

        //iss.str (usrInput);


        inputVector.clear();
        wordVector.clear();
        personVector.clear();
        orgVector.clear();
        notWordVector.clear();
        notPersonVector.clear();
        notOrgVector.clear();


    }





    return 0;

}