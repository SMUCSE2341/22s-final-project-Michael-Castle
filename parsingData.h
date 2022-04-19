//
// Created by Michael Ramenofsky on 4/10/22.
//

#ifndef INC_22S_FINAL_PROJ_PARSINGDATA_H
#define INC_22S_FINAL_PROJ_PARSINGDATA_H
#include "unordered_map"
#include "wordObject.h"
#include "iostream"
#include "DSAvlTree.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

class Directory{
public:
    unordered_map<string, bool> stopWords;
    DSTree<word> index;
    void createStopMap();
    void open_dir_using_filesystem(const std::string& directory);
    void open_dir_using_dirent(const std::string& directory);
    void ParseData (const std::string& filename);

};


#endif //INC_22S_FINAL_PROJ_PARSINGDATA_H
