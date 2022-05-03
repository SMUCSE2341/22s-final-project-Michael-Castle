//
// Created by willk on 5/3/2022.
//
#ifndef string
#include <string>
#include <cstring>
#include "vector"

#endif

#ifndef INC_22S_FINAL_PROJ_DSDOCUMENT_H
#define INC_22S_FINAL_PROJ_DSDOCUMENT_H




class DSDocument {
public:
    std::string ID;
    std::string text;
    bool operator<(const DSDocument& input) const {
        return ID<input.ID;
    }
    bool operator==(const DSDocument& input) const {
        return ID==input.ID;
    }
    std::vector<std::string> putWordsInVec(std::string allWords){
        std::string test = "";
        std::vector<std::string> v;
        for(int i = 0; i<allWords.size(); ++i)
        {
            if(allWords[i] !=  ' ')
                test += allWords[i];

            else if(allWords[i] == ' ')
            {
                v.push_back(test);
                test = "";
            }
        }
        return v;
    }


};

#endif //INC_22S_FINAL_PROJ_DSDOCUMENT_H
