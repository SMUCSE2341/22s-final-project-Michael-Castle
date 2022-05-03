//
// Created by willk on 4/18/2022.
//

#ifndef INC_22S_FINAL_PROJ_WORDOBJECT_H
#define INC_22S_FINAL_PROJ_WORDOBJECT_H

#include <string>
#include <vector>
using namespace std;

class word{
public:
    int count = 0;
    string id;
    vector<string> documents;

    word(string input) {
        id = input;
    }
    word() {

    }


    bool operator <(const word& input) {
        return id < input.id;
    }

    bool operator ==(const word& input) {
        return id == input.id;
    }
};

#endif //INC_22S_FINAL_PROJ_WORDOBJECT_H
