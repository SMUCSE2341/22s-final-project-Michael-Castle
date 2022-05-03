//
// Created by willk on 5/3/2022.
//
#ifndef string
#include <string>
#include <cstring>

#endif

#ifndef INC_22S_FINAL_PROJ_DSDOCUMENT_H
#define INC_22S_FINAL_PROJ_DSDOCUMENT_H




using namespace std;
class DSDocument {
public:
    string ID;
    string text;
    bool operator<(const DSDocument& input) {
        return ID<input.ID;
    }


};

#endif //INC_22S_FINAL_PROJ_DSDOCUMENT_H
