//
// Created by willk on 5/1/2022.
//
#include <string>
#include <vector>
#ifndef INC_22S_FINAL_PROJ_VECTORHELPER_H
#define INC_22S_FINAL_PROJ_VECTORHELPER_H
using namespace std;
#endif //INC_22S_FINAL_PROJ_VECTORHELPER_H
class vectorHelper {
public:
    vector<string> combineAnd(vector<string>*, vector<string>*);
    void pruneVector(vector<string>*);

    vector<string> combineOr(vector<string> *, vector<string> *);

    vector<string> combineNot(vector<string>*, vector<string> *);

};