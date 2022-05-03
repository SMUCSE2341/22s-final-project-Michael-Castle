//
// Created by willk on 5/1/2022.
//

#include "vectorHelper.h"

vector<string> vectorHelper::combineAnd(vector<string> *a, vector<string> *b) {
    vector<string> returnVector;

    for(string tmpA : *a) {
        for(string tmpB : *b) {
            if(tmpA == tmpB) {
                returnVector.push_back(tmpA);
            }
        }
    }

    return returnVector;
}



void vectorHelper::pruneVector(vector<string> *a) {
    for(int i = 0; i < a->size(); i++) {
        for(int j = i+1; j < a->size(); j++) {
            if(a->at(i) == a->at(j)) {
                a->erase(a->begin()+j);
                j--;
            }
        }
    }
}

vector<string> vectorHelper::combineOr(vector<string> *a, vector<string> *b) {
    vector<string> returnString;
    for(string tmpA : *a) {
        returnString.push_back(tmpA);
    }
    for(string tmpB : *b) {
        returnString.push_back(tmpB);
    }

    pruneVector(&returnString);
    return returnString;
}

vector<string> vectorHelper::combineNot(vector<string> *a, vector<string> *remove) {
    vector<string> returnVector = *a;

    for(int i = 0; i < remove->size(); i++) {
        for(int j = 0; j < returnVector.size(); j++) {
            if(returnVector.at(j) == remove->at(i)) {
                returnVector.erase(returnVector.begin()+j);
                j--;
            }
        }
    }

    return returnVector;
}




